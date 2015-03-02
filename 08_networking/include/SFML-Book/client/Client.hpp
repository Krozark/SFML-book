#ifndef BOOK_CLIENT_HPP
#define BOOK_CLIENT_HPP

#include <SFML-Book/common/Connection.hpp>

namespace book
{
    class Client : public Connection
    {
        public:
            Client(const Client&) = delete;
            Client& operator=(const Client&) = delete;

            Client();

            bool connect(const sf::IpAddress& ip, unsigned short port,sf::Time timeout=sf::Time::Zero);

            virtual sf::IpAddress getRemoteAddress()const;

        protected:
            unsigned int _port;
    };
}
#endif
