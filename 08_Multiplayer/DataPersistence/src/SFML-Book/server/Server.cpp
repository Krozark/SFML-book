#include <SFML-Book/server/Server.hpp>

#include <csignal>
#include <iostream>

#include <SFML-Book/server/Client.hpp>
#include <SFML-Book/server/Game.hpp>
#include <SFML-Book/server/EntityData.hpp>

#include <SFML-Book/common/FuncIds.hpp>
#include <SFML-Book/common/Packet.hpp>
#include <SFML-Book/common/random.hpp>



namespace book
{
    sig_atomic_t stop = false;

    void signalHandler(int sig)
    {
        std::cout<<"Signal recive. Stoping server, please wait."<<std::endl;
        stop = true;
    }

    Server::Server(int port) : _port(port),_gameThread(&Server::runGame,this), _listenThread(&Server::listen,this)
    {
        rand_init();
        _currentClient = nullptr;

        onLogOut = [this](Client* client){
            _clients.emplace_back(client);
        };
    }

    Server::~Server()
    {

        _clientMutex.lock();
        for(Client* client : _clients)
        {
            client->stop();
            delete client;
        }
        _clientMutex.unlock();

        delete _currentClient;
    }

    void Server::run()
    {
        std::signal(SIGINT,signalHandler);

        _gameThread.launch();
        _listenThread.launch();

        std::cout<<"Server is running"<<std::endl;

        _gameThread.wait();

        _listenThread.terminate();
    }

    void Server::runGame()
    {
        std::cout<<"Start Game service"<<std::endl;

        loadFromDb();
        while(!stop)
        {
            sf::Lock guard(_clientMutex);
            //for all clients
            for(auto it = _clients.begin(); it != _clients.end();++it)
            {
                Client* client = *it;
                packet::NetworkEvent* msg;
                while(client and client->pollEvent(msg))
                {
                    std::cout<<"Client "<<client->id()<<" recive data of type : "<<msg->type()<<std::endl;
                    switch(msg->type())
                    {
                        case FuncIds::IdGetListGame :
                        {
                            sf::Packet response;
                            packet::SetListGame list;
                            sf::Lock guard(_gameMutex);
                            for(auto game : _games)
                            {
                                list.add(game->id(),game->getPlayersCount(),game->getTeamCount());
                            }

                            response<<list;
                            client->send(response);
                        }break;
                        case FuncIds::IdCreateGame :
                        {
                            sf::Packet response;
                            packet::SetListGame list;
                            sf::Lock guard(_gameMutex);
                            _games.emplace_back(new Game("./media/map.json"));
                            _games.back()->load(true);

                            for(auto game : _games)
                            {
                                list.add(game->id(),game->getPlayersCount(),game->getTeamCount());
                            }
                            _games.back()->onLogOut = onLogOut;
                            _games.back()->run();

                            response<<list;
                            //send new game to all clients
                            for(auto it2 = _clients.begin(); it2 != _clients.end();++it2)
                                (*it2)->send(response);
                        }break;
                        case FuncIds::IdJoinGame :
                        {
                            int gameId = static_cast<packet::JoinGame*>(msg)->gameId();
                            sf::Lock guard(_gameMutex);
                            for(auto game : _games)
                            {
                                if(game->id() == gameId)
                                {
                                    if(game->addClient(client))
                                    {
                                        client = nullptr;
                                        it = _clients.erase(it);
                                        --it;
                                    }
                                    break;
                                }
                            }

                        }break;

                        case FuncIds::IdDisconnected :
                        {
                            it = _clients.erase(it);
                            --it;
                            client = nullptr;
                        }break;
                        default : break;
                    }
                    delete msg;
                }
            }
        }

        std::cout<<"Stop Game service"<<std::endl;
        {
            sf::Lock guard(_gameMutex);
            for(auto& game : _games)
            {
                std::cout<<"Stop Game "<<game->id()<<std::endl;
                game->stop();
                game->wait();
            }
            saveToDb();
        }
    }

    void Server::listen()
    {
        std::cout<<"Start Network service"<<std::endl;
        if(_socketListener.listen(_port) != sf::Socket::Done)
        {
            stop = true;
            std::cout<<"Error whene initializing port "<<_port<<". Stopping server"<<std::endl;
            return;
        }

        _currentClient = new Client;
        while(!stop)
        {
            std::cout<<"Waiting for new connections"<<std::endl;
            if (_socketListener.accept(_currentClient->getSockIn()) == sf::Socket::Done)
            {
                std::cout<<"New connection received from " << _currentClient->getRemoteAddress()<<std::endl;
                if(_currentClient->connect())
                {
                    std::cout<<"Client accepted"<<std::endl;

                    sf::Lock guard(_clientMutex);

                    _clients.emplace_back(_currentClient);
                    _currentClient->run();

                    _currentClient = new Client;
                }
                else
                {
                    std::cout<<"Client rejected"<<std::endl;
                    _currentClient->disconnect();
                }
            }
        }

        std::cout<<"Stop Network service"<<std::endl;
    }

    void Server::saveToDb()
    {
        std::cout<<"Saving Games"<<std::endl;
        for(auto game : _games)
        {
            std::cout<<"Saving game "<<game->id()<<std::endl;
            game->save();
        }
        std::cout<<"Done"<<std::endl;
    }

    void Server::loadFromDb()
    {
        std::cout<<"Loading Games"<<std::endl;
        Game::result_type games = Game::all();
        for(Game::type_ptr g: games)
        {
            g->onLogOut = onLogOut;
            g->run();
            _games.emplace_back(std::move(g));

        }

        std::cout<<"Done"<<std::endl;
    }

}
