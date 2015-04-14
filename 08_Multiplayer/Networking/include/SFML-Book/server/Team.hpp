#ifndef BOOK_TEAM_HPP
#define BOOK_TEAM_HPP

#include <vector>
#include <list>
#include <cstdint>

#include <SFML/Graphics.hpp>

namespace book
{
    class Client;
    class Game;

    class Team
    {
        public:
            Team(const Team&) = delete;
            Team& operator=(const Team&) = delete;

            Team(int id,const sf::Color& color,int gold,Game& game);

            void addGold(int amount);
            int getGold()const;

            void addEnemy(Team* team);
            const std::vector<Team*>& getEnemies()const;

            void  addQgId(std::uint32_t);
            const std::vector<std::uint32_t>& getQgIds()const;
            void removeQgId(std::uint32_t id);

            int id()const;
            const sf::Color& getColor()const;

            void add(Client* client);
            void remove(Client* client);

            const std::list<Client*>& getClients()const;

            bool isGameOver()const;


        private:
            bool _isAlive;
            const int _id;
            int _gold;
            std::vector<std::uint32_t> _QGId;
            sf::Color _color;
            Game& _game;

            std::vector<Team*> _enemies;
            std::list<Client*> _clients;
    };
}
#endif
