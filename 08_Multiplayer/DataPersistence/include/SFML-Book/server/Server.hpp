#ifndef BOOK_SERVER_HPP
#define BOOK_SERVER_HPP

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <list>
#include <memory>

class Game;

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
            sf::Mutex _gameMutex;
            std::list<std::shared_ptr<Game>> _games;
            sf::Mutex _clientMutex;
            std::list<Client*> _clients;

            sf::Thread _listenThread;
            sf::TcpListener _socketListener;
            Client* _currentClient;

            using FuncType = std::function<void(book::Client*)>;
            FuncType onLogOut;

            void saveToDb();
            void loadFromDb();
    };
}
#endif
