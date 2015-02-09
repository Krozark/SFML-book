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

            bool connect();
            virtual sf::IpAddress getRemoteAddress()const;

            sf::TcpSocket& getSockIn();

    };
}
#endif
