#ifndef BOOK_CLIENT_HPP
#define BOOK_CLIENT_HPP

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

namespace book
{
    class Client
    {
        public:
            Client(const Client&) = delete;
            Client& operator=(const Client&) = delete;

            Client();
            bool connect(const sf::IpAddress& ip, unsigned short port,sf::Time timeout=sf::Time::Zero);

        protected:
            unsigned int _port;

        private:
            sf::TcpSocket _sockIn;
            sf::TcpSocket _sockOut;
    };
}
#endif
