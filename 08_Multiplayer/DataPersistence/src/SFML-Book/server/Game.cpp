#include <SFML-Book/server/Game.hpp>

#include <SFML-Book/server/Client.hpp>
#include <SFML-Book/server/Team.hpp>
#include <SFML-Book/server/Component.hpp>
#include <SFML-Book/server/System.hpp>

#include <SFML-Book/common/random.hpp>


#include <utils/json/Driver.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

namespace book
{
    int Game::_numberOfCreations = 0;

    Game::Game(const std::string& mapFileName) :
        _isRunning(false),
        _gameThread(&Game::_run,this),
        _map(sfutils::VMap::createMapFromFile(mapFileName)),
        _sendThread(&Game::_send,this),
        _id(++_numberOfCreations),
        _mapFileName(mapFileName)
    {
        if(_map == nullptr)
            throw std::runtime_error("Impossible to load file map");
        _map->clear();//we just need the geometry here

        int initialGold = 0;
        std::vector<sf::Vector2i> spawns;
        {
            utils::json::Value* rootPtr = utils::json::Driver::parse_file(mapFileName);

            utils::json::Object& root = *rootPtr;
            const utils::json::Object& size = root["size"];
            const utils::json::Object& min = size["min"];
            const utils::json::Object& max = size["max"];

            _minCoord.x = min["x"].as_int();
            _minCoord.y = min["y"].as_int();

            _maxCoord.x = max["x"].as_int();
            _maxCoord.y = max["y"].as_int();

            const utils::json::Object& players = root["players"];
            const utils::json::Array& spawn = players["spawn"];

            for(const utils::json::Object& value : spawn)
                spawns.emplace_back(value["x"].as_int(),value["y"].as_int());

            initialGold = players["gold"].as_int();
        }
        
        for(unsigned int i = 0; i<spawns.size();++i)
        {
            Team* team = new Team(i,sf::Color(random(110,225),
                                              random(110,225),
                                              random(110,225)
                                             ),
                                  initialGold,
                                  *this);

            createEntity(spawns[i],team,makeAsMain);
            _teams.emplace_back(team);
        }

        //add enemies
        for(unsigned int i=0; i<spawns.size();++i)
        {
            for(unsigned int j=0; j<spawns.size();++j)
            {
                if(i!=j)
                {
                    _teams[i]->addEnemy(_teams[j]);
                }
            }
        }

        systems.add<SysAIMain>(*this);
        systems.add<SysAIWarrior>(*this);
        systems.add<SysAIDefender>(*this);
        systems.add<SysAISpawner>(*this);
        systems.add<SysAIWalker>(*this);
        systems.add<SysAIFlyer>(*this);
        systems.add<SysHp>(*this);
    }

    Game::~Game()
    {
        for(Client* client: _clients)
            delete client;

        for(Team* team : _teams)
            delete team;
    }

    int Game::getTeamCount()
    {
        sf::Lock guard(_teamMutex);
        return _teams.size();
    }

    int Game::getPalyersCount()
    {
        sf::Lock guard(_clientsMutex);
        return _clients.size();
    }

    int Game::id()const
    {
        return _id;
    }

    bool Game::addClient(Client* client)
    {
        sf::Lock guard(_teamMutex);
        Team* clientTeam = nullptr;
        for(Team* team : _teams)
        {
            if(team->getClients().size() == 0 and team->isGameOver())
            {
                clientTeam = team;
                break;
            }
        }

        sf::Packet response;
        if(clientTeam != nullptr)
        {
            //send map informations
            std::ifstream file(_mapFileName);
            std::string content((std::istreambuf_iterator<char>(file)),(std::istreambuf_iterator<char>()));

            packet::JoinGameConfirmation conf(content,clientTeam->id());
            for(Team* team : _teams)
            {
                packet::JoinGameConfirmation::Data data;
                data.team = team->id();
                data.gold = team->getGold();
                data.color = team->getColor();

                conf.addTeam(std::move(data));
            }
            response<<conf;

            client->send(response);

            {
                //send initial content
                response.clear();
                sf::Lock gameGuard(_gameMutex);
                packet::CreateEntity datas;

                for(auto id : entities)
                    addCreate(datas,id);

                response<<datas;
                client->send(response);
            }

            std::cout<<"Add client to game"<<std::endl;

            client->setTeam(clientTeam);

            sf::Lock guardClients(_clientsMutex);
            _clients.emplace_back(client);
        }
        else
        {
            response<<packet::JoinGameReject(_id);
            client->send(response);
        }

        return clientTeam != nullptr;
    }


    void Game::run()
    {
        _isRunning = true;
        _gameThread.launch();
        _sendThread.launch();
    }

    void Game::stop()
    {
        _isRunning = false;
    }

    Entity& Game::createEntity(const sf::Vector2i& coord,Team* team,MakeAs makeAs)
    {
        std::uint32_t id = entities.create();
        Entity& e = entities.get(id);

        makeAs(e,team,*this);

        e.setPosition(_map->mapCoordsToPixel(coord),coord);
        _byCoords[coord].emplace_back(&e);

        addCreate(_createEntities,id);
        return e;
    }

    void Game::markEntityUpdated(std::uint32_t id)
    {
        _updateEntitiesId.insert(id);
    }

    void Game::markEntityHit(std::uint32_t id,std::uint32_t enemyId)
    {
        packet::OnHitEntity::Data data;
        data.entityId = id;
        data.entityCoord = entities.get(id).getCoord();
        data.enemyId = enemyId;
        data.enemyCoord = entities.get(id).getCoord();

        _onHit.emplace_back(std::move(data));
    }

    void Game::markEntityHitted(std::uint32_t id,std::uint32_t enemyId)
    {
        packet::OnHittedEntity::Data data;
        data.entityId = id;
        data.entityCoord = entities.get(id).getCoord();
        data.enemyId = enemyId;
        data.enemyCoord = entities.get(id).getCoord();

        _onHitted.emplace_back(std::move(data));
    }

    void Game::markEntitySpawn(std::uint32_t id)
    {
        _onSpawn.insert(id);
    }

    void Game::markTeamUpdated(std::uint32_t id)
    {
        _updateTeamId.insert(id);
    }

    void Game::destroyEntity(std::uint32_t id)
    {
        Entity& e = entities.get(id);
        const sf::Vector2i coord = e.getCoord();

        _byCoords[coord].remove(&e);
        entities.remove(id);
        _destroyEntityId.emplace_back(id);
    }

    void Game::setPosition(Entity& e,const sf::Vector2i& oldCoord,const sf::Vector2f& oldPos,const sf::Vector2i& newCoord, const sf::Vector2f& newPos)
    {
        markEntityUpdated(e.id());
        e.setPosition(newPos,newCoord);

        if(oldCoord != newCoord)
        {
            _byCoords[oldCoord].remove(&e);
            _byCoords[newCoord].emplace_back(&e);
        }
    }


    sf::Vector2i Game::mapPixelToCoords(const sf::Vector2f& pos)const
    {
        return _map->mapPixelToCoords(pos);
    }

    sf::Vector2f Game::mapCoordsToPixel(const sf::Vector2i& pos)const
    {
        return _map->mapCoordsToPixel(pos);
    }

    std::list<Entity*> Game::getByCoords(const sf::Vector2i& coord)
    {
        return _byCoords[coord];
    }

    sf::Vector2i Game::getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const
    {
        return _map->getPath1(origin,dest);
    }

    int Game::getDistance(const sf::Vector2i& origin,const sf::Vector2i& dest)const
    {
        return _map->getDistance(origin,dest);
    }


    void Game::_run()
    {
        sf::Clock clock;        
        sf::Time timeSinceLastUpdate;

        sf::Time TimePerFrame = sf::seconds(1.f/120);

        while(_isRunning)
        {
            sf::Lock gameGuard(_gameMutex);
            processNetworkEvents();

            sf::Time delta = clock.restart();
            timeSinceLastUpdate += delta;
            if(timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                update(TimePerFrame);
            }
        }
    }

    void Game::_send()
    {
        while(_isRunning)
        {
            _sendMutex.lock();
            if(_outgoing.size() > 0)
            {
                sf::Packet packet = _outgoing.front();
                _outgoing.pop();
                _sendMutex.unlock();

                sf::Lock guard(_clientsMutex);
                for(auto it = _clients.begin(); it != _clients.end();++it)
                {
                    (*it)->send(packet);
                }
            }
            else
            {
                _sendMutex.unlock();
            }
        }
    }

    void Game::processNetworkEvents()
    {
        sf::Lock guard(_clientsMutex);
        for(auto it = _clients.begin(); it != _clients.end();++it)
        {
            Client* client = *it;
            packet::NetworkEvent* msg;
            while(client and client->pollEvent(msg))
            {
                switch(msg->type())
                {
                    case FuncIds::IdDisconnected :
                    {
                        it = _clients.erase(it);
                        --it;
                        delete client;
                        client = nullptr;
                    }break;
                    case FuncIds::IdLogOut :
                    {
                        it = _clients.erase(it);
                        --it;
                        client->getTeam()->remove(client);
                        
                        onLogOut(client);
                        client = nullptr;
                    }break;
                    case FuncIds::IdRequestCreateEntity :
                    {
                        packet::RequestCreateEntity* event = static_cast<packet::RequestCreateEntity*>(msg);

                        sf::Lock gameGuard(_teamMutex);
                        short int entityType = event->getType();
                        int gold = client->getTeam()->getGold();
                        sf::Vector2i coord = event->getCoord();


                        for(EntityType::Info& info : EntityType::informations)
                        {
                            if(info.makeAs == entityType
                               and gold >= info.cost
                               and _byCoords[coord].size() == 0)
                            {
                                MakeAs makeAs = getMakeAs(info.makeAs);
                                if(makeAs != nullptr)
                                {
                                    createEntity(coord,client->getTeam(),makeAs);
                                    client->getTeam()->addGold(-info.cost);
                                }
                            }
                        }
                    }break;
                    case FuncIds::IdRequestDestroyEntity :
                    {
                        packet::RequestDestroyEntity* event = static_cast<packet::RequestDestroyEntity*>(msg);
                        unsigned int id = event->getId();

                        if(entities.isValid(id))
                        {
                            sf::Lock gameGuard(_teamMutex);
                            CompTeam::Handle team = entities.getComponent<CompTeam>(id);
                            if(team.isValid())
                            {
                                if(team->_team->id() == client->getTeam()->id())
                                {
                                    destroyEntity(id);
                                }
                            }
                        }
                    }break;
                    default : break;
                }
            }
        }
    }
    void Game::sendUpdates()
    {

        if(_onHit.size() > 0)
        {
            packet::OnHitEntity update;
            for(packet::OnHitEntity::Data& data: _onHit)
            {
                update.add(std::move(data));
            }

            sf::Packet packet;
            packet<<update;
            sendToAll(packet);

            _onHit.clear();
        }

        if(_onHitted.size() > 0)
        {
            packet::OnHittedEntity update;
            for(packet::OnHittedEntity::Data& data : _onHitted)
            {
                update.add(std::move(data));
            }

            sf::Packet packet;
            packet<<update;
            sendToAll(packet);

            _onHitted.clear();
        }

        if(_onSpawn.size() > 0)
        {
            packet::OnSpawnEntity update;
            for(std::uint32_t id : _onSpawn)
                update.add(id);

            sf::Packet packet;
            packet<<update;
            sendToAll(packet);

            _onSpawn.clear();
        }
        
        if(_destroyEntityId.size() > 0)
        {
            packet::DestroyEntity update;
            for(std::uint32_t id : _destroyEntityId)
                update.add(id);

            sf::Packet packet;
            packet<<update;
            sendToAll(packet);

            _destroyEntityId.clear();
        }

        if(_createEntities.getCreates().size() >0)
        {
            sf::Packet packet;
            packet<<_createEntities;
            sendToAll(packet);

            _createEntities.clear();
        }
        
        if(_updateEntitiesId.size() > 0)
        {
            packet::UpdateEntity update;

            for(std::uint32_t id : _updateEntitiesId)
                addUpdate(update,id);

            sf::Packet packet;
            packet<<update;
            sendToAll(packet);

            _updateEntitiesId.clear();
        }

        if(_updateTeamId.size() > 0)
        {
            packet::UpdateTeam update;
            sf::Lock guard(_teamMutex);
            for(std::uint32_t id : _updateTeamId)
            {
                packet::UpdateTeam::Data data;
                data.team = id;
                data.gameOver = _teams[id]->isGameOver();
                data.gold = _teams[id]->getGold();

                update.add(std::move(data));
            }
            sf::Packet packet;
            packet<<update;
            sendToAll(packet);

            _updateTeamId.clear();
        }
    }

    void Game::update(sf::Time deltaTime)
    {
        Application::update(deltaTime);
        sendUpdates();
    }

    void Game::sendToAll(sf::Packet& packet)
    {
        sf::Lock guard(_sendMutex);
        _outgoing.emplace(packet);
    }

    void Game::addUpdate(packet::UpdateEntity& packet,unsigned int id)
    {
        if(entities.isValid(id))
        {
            Entity& e = entities.get(id);
            packet::UpdateEntity::Data update;

            update.entityId = id;
            update.animationId = entities.getComponent<CompSkin>(id)->_animationId;
            update.position = e.getPosition();
            update.coord = e.getCoord();
            update.hp = entities.getComponent<CompHp>(id)->_hp;

            packet.add(std::move(update));
        }
    }

    void Game::addCreate(packet::CreateEntity& packet,unsigned int id)
    {
        Entity& e = entities.get(id);
        packet::CreateEntity::Data update;
        
        update.entityId = id;
        update.entityType = e.getType();
        update.entityTeam = entities.getComponent<CompTeam>(id)->_team->id();
        update.animationId = entities.getComponent<CompSkin>(id)->_animationId;
        update.position = e.getPosition();
        update.coord = e.getCoord();
        update.maxHp = entities.getComponent<CompHp>(id)->_maxHp;
        update.hp = entities.getComponent<CompHp>(id)->_hp;

        packet.add(std::move(update));
    }
}
