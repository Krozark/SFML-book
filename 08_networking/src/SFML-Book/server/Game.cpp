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
        _running(false),
        _thread(&Game::_run,this),
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
            sf::Lock guard(_clientsMutex);
            res = _clients.size() < Team::MAX_TEAMS;
        }

        sf::Packet response;
        if(res == true)
        {
            std::ifstream file(_mapFileName);
            std::string content((std::istreambuf_iterator<char>(file)),(std::istreambuf_iterator<char>()));

            response<<packet::JoinGameConfirmation(content,
                                                    sf::Color(random(110,225),
                                                              random(110,225),
                                                              random(110,225)
                                                              ));
            client->send(response);

            std::cout<<"Add client to game"<<std::endl;

            sf::Lock guard(_clientsMutex);
            _clients.emplace_back(client);
        }
        else
        {
            response<<packet::JoinGameReject(_id);
            client->send(response);
        }

        return res;
    }

    void Game::run()
    {
        _running = true;
        _thread.launch();
    }

    void Game::stop()
    {
        _running = false;
    }

    void Game::_run()
    {
        sf::Clock clock;        
        while(_running)
        {
            processNetworkEvents();
            update(clock.restart());
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
