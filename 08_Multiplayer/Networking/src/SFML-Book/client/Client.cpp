#include <SFML-Book/client/Client.hpp>

#include <iostream>

namespace book
{
    Client::Client()
    {
    }

    bool Client::connect(const sf::IpAddress& ip,unsigned short port,sf::Time timeout)
    {
        bool res = false;
        std::cout<<"Connect to server "<<ip<<std::endl;
        sf::TcpListener socketListener;
        if(_sockOut.connect(ip,port,timeout) == sf::Socket::Status::Done)
        {
            std::cout<<"Connected to server.\nCreating second connection ..."<<std::endl;
            int retry = 100;
            port+=10;
            while(socketListener.listen(port) != sf::Socket::Status::Done and retry > 0)
            {
                ++port;
                --retry;
            }

            if(retry>0)
            {
                sf::Packet packet;
                packet<<sf::Int32(FuncIds::IdHandler) << sf::Uint32(port);

                std::cout<<"Send informations to server (port="<<port<<")"<<std::endl;
                if(_sockOut.send(packet) == sf::Socket::Done)
                {
                    std::cout<<"Wait for server connection"<<std::endl;
                    if(socketListener.accept(_sockIn) == sf::Socket::Done)
                    {
                        std::cout<<"Connection Receive. All is good."<<std::endl;
                        res = true;
                    }
                    else
                        std::cout<<"Failed"<<std::endl;
                }
                else
                    std::cout<<"Failed"<<std::endl;
            }
            else
                std::cout<<"Failed"<<std::endl;
        }
        else
            std::cout<<"Failed"<<std::endl;

        return res;
    }

    sf::IpAddress Client::getRemoteAddress()const
    {
        return _sockOut.getRemoteAddress();
    }
}
