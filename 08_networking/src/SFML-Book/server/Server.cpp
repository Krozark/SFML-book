#include <SFML-Book/server/Server.hpp>

#include <csignal>
#include <iostream>

#include <SFML-Book/server/Client.hpp>
#include <SFML-Book/common/FuncIds.hpp>

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

        _currentClient = new Client;
        while(!stop)
        {
            std::cout<<"Waiting for new connections"<<std::endl;
            if (_socketListener.accept(_currentClient->sockIn) == sf::Socket::Done)
            {
                std::cout<<"New connection received from " << _currentClient->sockIn.getRemoteAddress()<<std::endl;
                if(connect(*_currentClient))
                {
                    std::cout<<"Client accepted"<<std::endl;
                    _clients.emplace_back(_currentClient);
                    _currentClient = new Client;
                }
                else
                {
                    std::cout<<"Client rejected"<<std::endl;
                    _currentClient->sockIn.disconnect();
                }
            }
        }

        std::cout<<"Stop Network service"<<std::endl;
    }

    bool Server::connect(Client& client)
    {
        bool res = false;
        sf::Packet packet;
        std::cout<<"Get datas"<<std::endl;
        if(client.sockIn.receive(packet) == sf::Socket::Done)
        {
            sf::Int32 fid;

            packet>>fid;
            std::cout<<"Receive datas. Compare them to expected one"<<std::endl;
            if(fid ==  FuncIds::IdHandler)
            {
                sf::Uint32 port;
                packet>>port;
                std::cout<<"Connect to given port ("<<port<<")"<<std::endl;
                if(client.sockOut.connect(client.sockIn.getRemoteAddress(),port,sf::seconds(5)) == sf::Socket::Status::Done)
                {
                    std::cout<<"All is good"<<std::endl;
                    res = true;
                }
                else
                    std::cout<<"Failed"<<std::endl;
            }
            else
                std::cout<<"Error. Fuction id is not IdHandler"<<std::endl;
        }
        else
            std::cout<<"Failed"<<std::endl;
        return res;
    }
}
