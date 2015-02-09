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
            
            int getTeamCount();
            int getPalyersCount();

            int id()const;

        protected:


        private:
            sf::Mutex _teamMutex;
            std::vector<Team*> _teams;

            sf::Mutex _clientsMutex;
            std::vector<Client*> _clients;

            const int _id;
            static int _numberOfCreations;
    };
}
#endif
