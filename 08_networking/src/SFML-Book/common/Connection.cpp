#include <SFML-Book/common/Connection.hpp>

#include <SFML-Book/common/Packet.hpp>

#include <iostream>

namespace book
{

    int Connection::_numberOfCreations = 0;
    
    Connection::Connection() :_isRunning(false), _receiveThread(&Connection::_receive,this), _sendThread(&Connection::_send,this),_id(++_numberOfCreations)
    {
    }

    Connection::~Connection()
    {
    }

    void Connection::run()
    {
        std::cout<<"Connection "<<_id<<" is runing"<<std::endl;
        _isRunning = true;
        _receiveThread.launch();
        _sendThread.launch();
    }

    void Connection::stop()
    {
        _isRunning  = false;
        std::cout<<"Connection "<<_id<<" is stoped"<<std::endl;
    }

    void Connection::wait()
    {
        _receiveThread.wait();
        _sendThread.wait();
    }

    int Connection::id()const
    {
        return _id;
    }

    bool Connection::pollEvent(sf::Packet& event)
    {
        bool res = false;
        sf::Lock guard(_receiveMutex);
        if(_incoming.size() > 0)
        {
            std::swap(event,_incoming.front());
            _incoming.pop();
            res = true;
        }
        return res;
    }

    
    bool Connection::pollEvent(packet::NetworkEvent*& event)
    {
        bool res = false;
        sf::Packet msg;
        if(Connection::pollEvent(msg))
        {
            event = packet::NetworkEvent::makeFromPacket(msg);
            if(event != nullptr)
                res = true;
        }
        return res;
    }

    void Connection::send(sf::Packet& packet)
    {
        sf::Lock guard(_sendMutex);
        _outgoing.emplace(packet);
    }


    void Connection::disconnect()
    {
        _sockIn.disconnect();
        _sockOut.disconnect();
    }

    void Connection::_receive()
    {
        sf::SocketSelector selector;
        selector.add(_sockIn);

        while(_isRunning)
        {
            if(not selector.wait(sf::seconds(1)))
                continue;

            if(not selector.isReady(_sockIn))
                continue;

            sf::Packet packet;
            sf::Socket::Status status = _sockIn.receive(packet);
            if(status == sf::Socket::Done)
            {
                sf::Lock guard(_receiveMutex);
                _incoming.emplace(std::move(packet));
            }
            else if (status == sf::Socket::Disconnected)
            {
                packet.clear();
                packet<<packet::Disconnected();
                sf::Lock guard(_receiveMutex);
                _incoming.emplace(std::move(packet));

                stop();
            }
        }
    }

    void Connection::_send()
    {
        while(_isRunning)
        {
            _sendMutex.lock();
            if(_outgoing.size() > 0)
            {
                sf::Packet packet = _outgoing.front();
                _outgoing.pop();
                _sendMutex.unlock();
                _sockOut.send(packet);
            }
            else
            {
                _sendMutex.unlock();
            }

        }
    }
}
