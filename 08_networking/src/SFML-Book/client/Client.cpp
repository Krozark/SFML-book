#include <SFML-Book/client/Client.hpp>

namespace book
{
    Client::Client()
    {
    }

    bool Client::connect(const sf::IpAddress& ip,unsigned short port,sf::Time timeout)
    {
        bool res = false;
        if(_sockOut.connect(ip,port,timeout) == sf::Socket::Status::Done)
        {
            res = true;
            sf::Packet packet;
            packet<<sf::Int32(42);
            _sockOut.send(packet);
        }
        return res;
    }
}
