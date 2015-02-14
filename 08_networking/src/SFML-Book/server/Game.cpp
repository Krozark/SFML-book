#include <SFML-Book/server/Game.hpp>

#include <SFML-Book/server/Client.hpp>
#include <SFML-Book/server/Team.hpp>
#include <SFML-Book/server/Component.hpp>

#include <SFML-Book/common/random.hpp>

#include <iostream>
#include <fstream>

namespace book
{
    int Game::_numberOfCreations = 0;

    Game::Game(const std::string& mapFileName) :
        _isRunning(false),
        _gameThread(&Game::_run,this),
        _sendThread(&Game::_send,this),
        _id(++_numberOfCreations),
        _mapFileName(mapFileName)
    {
        //TODO parse map to get initial gold, and team position
        for(int i = 0; i<Team::MAX_TEAMS;++i)
        {
            _teams.emplace_back(new Team(sf::Color(random(110,225),
                                                   random(110,225),
                                                   random(110,225)
                                                  )));
        }

        /*systems.add<SysAIMain>();
        systems.add<SysAIWarrior>(*this);
        systems.add<SysAIDefender>(*this);
        systems.add<SysAISpawner>(*this);
        systems.add<SysAIWalker>(*this);
        systems.add<SysAIFlyer>(*this);
        systems.add<SysHp>(*this);
        systems.add<SysEffect>(*this);*/
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
            if(team->getClients().size() == 0)
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

            response<<packet::JoinGameConfirmation(content,clientTeam->getColor());

            client->send(response);

            {
                //send initial content
                response.clear();
                sf::Lock gameGuard(_gameMutex);
                packet::UpdateEntity datas;

                for(auto id : entities)
                    addUpdate(datas,id);

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

    void Game::addUpdate(packet::UpdateEntity& packet,unsigned int id)
    {
        Entity& e = entities.get(id);
        packet::UpdateEntity::Update update;
        
        update.entityId = id;
        update.entityType = e.getType();
        update.animationId = entities.getComponent<CompSkin>(id)->_animationId;
        update.position = e.getPosition();
        update.coord = e.getCoord();
        update.hp = entities.getComponent<CompHp>(id)->_hp;

        packet.add(std::move(update));
    }

    void Game::_run()
    {
        sf::Clock clock;        
        sf::Time timeSinceLastUpdate;

        sf::Time TimePerFrame = sf::seconds(1.f/120);

        while(_isRunning)
        {
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
                    case FuncIds::IdCreateEntity :
                    {
                    }break;
                    case FuncIds::IdDestroyEntity :
                    {
                    }break;
                    case FuncIds::IdDisconnected :
                    {
                        it = _clients.erase(it);
                        --it;
                        client = nullptr;
                    }break;
                    default : break;
                }
            }
        }
    }

    void Game::update(sf::Time deltaTime)
    {
        Application::update(deltaTime);
        /*
        IdDestroyEntity, //client and server
            IdMoveEntity, //server
            IdHittedEntity, //server
            IdHitEntity, //server
            IdSetAnimationEntity, //server
            IdAddGoldTeam, //server
        */
    }

    void Game::sendToAll(sf::Packet& packet)
    {
        sf::Lock guard(_sendMutex);
        _outgoing.emplace(packet);
    }
}
