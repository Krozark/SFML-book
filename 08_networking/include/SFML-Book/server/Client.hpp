#ifndef BOOK_CLIENT_HPP
#define BOOK_CLIENT_HPP

#include <SFML/Network.hpp>

namespace book
{
    class Client
    {
        public:
            Client();
            Client(const Client&) = delete;
            Client& operator=(const Client&) = delete;

            sf::TcpSocket sockIn;
            sf::TcpSocket sockOut;

        private:
    };
}
#endif
