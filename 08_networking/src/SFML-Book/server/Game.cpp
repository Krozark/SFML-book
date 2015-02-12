#include <SFML-Book/server/Game.hpp>

#include <SFML-Book/server/Client.hpp>
#include <SFML-Book/server/Team.hpp>

#include <SFML-Book/common/Packet.hpp>
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
        //send map informations

        bool res = false;
        {
            sf::Lock guard(_teamMutex);
            res = _teams.size() < Team::MAX_TEAMS;
            //or _teams->getClients.size() == 0
        }

        sf::Packet response;
        if(res == true)
        {
            std::ifstream file(_mapFileName);
            std::string content((std::istreambuf_iterator<char>(file)),(std::istreambuf_iterator<char>()));

            //TODO set color to team
            response<<packet::JoinGameConfirmation(content,
                                                    sf::Color(random(110,225),
                                                              random(110,225),
                                                              random(110,225)
                                                              ));
            client->send(response);

            std::cout<<"Add client to game"<<std::endl;

            sf::Lock guardTeam(_teamMutex);
            Team* team =new Team();
            _teams.emplace_back(team);
            client->setTeam(team);

            sf::Lock guardClients(_clientsMutex);
            _clients.emplace_back(client);
        }
        else
        {
            response<<packet::JoinGameReject(_id);
            client->send(response);
        }

        return res;
    }

    void Game::sendToAll(sf::Packet& packet)
    {
        sf::Lock guard(_sendMutex);
        _outgoing.emplace(packet);
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
        /*
        IdDestroyEntity, //client and server
            IdMoveEntity, //server
            IdHittedEntity, //server
            IdHitEntity, //server
            IdSetAnimationEntity, //server
            IdAddGoldTeam, //server
        */
    }
}
