#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <vector>
#include <string>
#include <queue>

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

namespace book
{
    class Team;
    class Client;

    class Game
    {
        public:
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            Game(const std::string& mapFileName);
            ~Game();
            
            int getTeamCount();
            int getPalyersCount();

            int id()const;

            bool addClient(Client* client);
            void sendToAll(sf::Packet& packet);

            void run();
            void stop();

        protected:


        private:
            bool _isRunning;
            sf::Thread _gameThread;
            
            sf::Mutex _teamMutex;
            std::vector<Team*> _teams;

            sf::Mutex _clientsMutex;
            std::vector<Client*> _clients;

            void _send();
            sf::Thread _sendThread;
            sf::Mutex _sendMutex;
            std::queue<sf::Packet> _outgoing;

            const int _id;
            static int _numberOfCreations;

            void _run();

            std::string _mapFileName;

            void processNetworkEvents();
            void update(sf::Time deltaTime);

    };
}
#endif
