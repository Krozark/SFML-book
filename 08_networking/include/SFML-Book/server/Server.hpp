#ifndef BOOK_SERVER_HPP
#define BOOK_SERVER_HPP

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <list>


namespace book
{
    class Client;
    class Game;

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

            static bool connect(Client& client);

            sf::Thread _gameThread;
            sf::SocketSelector _gameSelector;
            std::list<Client*> _clients;
            std::list<Game*> _games;


            sf::Thread _listenThread;
            sf::TcpListener _socketListener;
            Client* _currentClient;


    };
}
#endif
