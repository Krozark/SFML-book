#ifndef BOOK_SERVER_HPP
#define BOOK_SERVER_HPP

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <list>


namespace book
{
    class Client;

    class Server
    {
        public:
            Server(const Server&) = delete;
            Server& operator=(const Server&) = delete;

            Server(int port);
            ~Server();

            void run();

        private:

            const unsigned int _port;

            void runGame();
            void listen();

            sf::Thread _gameThread;
            sf::Thread _listenThread;

            sf::TcpListener _socketListener;
            Client* _currentClient;
            std::list<Client*> _clients;
    };
}
#endif
