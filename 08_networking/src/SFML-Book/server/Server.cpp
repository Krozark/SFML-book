#include <SFML-Book/server/Server.hpp>

#include <csignal>
#include <iostream>

#include <SFML-Book/server/Client.hpp>

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
        _currentClient = nullptr;
    }

    Server::~Server()
    {
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
        while(!stop)
        {
        }
        std::cout<<"Stop Game service"<<std::endl;
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
        std::cout<<"Waiting for connections"<<std::endl;

        _currentClient = new Client;
        while(!stop)
        {
            if (_socketListener.accept(_currentClient->sockIn) == sf::Socket::Done)
            {
                std::cout<<"New connection received from " << _currentClient->sockIn.getRemoteAddress()<<std::endl;
                _clients.emplace_back(_currentClient);
                _currentClient = new Client;
            }
            else
            {
                std::cout<<"Dafuck"<<std::endl;
            }
        }

        std::cout<<"Stop Network service"<<std::endl;
    }
}
