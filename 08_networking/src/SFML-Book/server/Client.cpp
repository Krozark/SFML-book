#include <SFML-Book/server/Client.hpp>

#include <iostream>

namespace book
{

    int Client::_numberOfCreations = 0;
    
    Client::Client() :_isRunning(false), _receiveThread(&Client::_receive,this), _sendThread(&Client::_send,this),_id(++_numberOfCreations)
    {
    }

    void Client::run()
    {
        std::cout<<"Client "<<_id<<" is runing"<<std::endl;
        _isRunning = true;
        _receiveThread.launch();
        _sendThread.launch();
    }

    void Client::stop()
    {
        _isRunning  = false;
        std::cout<<"Client "<<_id<<" is stoped"<<std::endl;
    }

    int Client::id()const
    {
        return _id;
    }

    bool Client::poolEvent(sf::Packet& event)
    {
        return false;
    }

    void Client::send(sf::Packet& packet)
    {
    }

    void Client::_receive()
    {
        sf::SocketSelector selector;
        selector.add(_sockIn);

        while(_isRunning)
        {
            if(not selector.wait(sf::seconds(1)))
                continue;

            if(not selector.isReady(_sockIn))
                continue;
            
        }
    }

    void Client::_send()
    {
        while(_isRunning)
        {
            _sendMutex.lock();
            if(_outgoing.size() > 0)
            {
                sf::Packet packet = _outgoing.front();
                _outgoing.pop();
                _sendMutex.unlock();
                int retry = 3;
                while(retry > 0 and _sockOut.send(packet) != sf::Socket::Done)
                {
                    --retry;
                }
            }
            else
            {
                _sendMutex.unlock();
            }

        }
    }
}
