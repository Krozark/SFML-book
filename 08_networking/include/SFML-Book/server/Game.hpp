#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <vector>
#include <SFML/System.hpp>

namespace book
{
    class Team;
    class Client;
    class Game
    {
        public:
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            Game();
            
            std::size_t getTeamCount();
            std::size_t getPalyersCount();

        protected:


        private:
            sf::Mutex _teamMutex;
            std::vector<Team*> _teams;

            sf::Mutex _clientsMutex;
            std::vector<Client*> _clients;
    };
}
#endif
