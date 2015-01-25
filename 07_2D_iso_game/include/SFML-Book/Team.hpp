#ifndef BOOK_TEAM_HPP
#define BOOK_TEAM_HPP

#include <SFML/Graphics.hpp>
#include <SFML-Book/TeamGui.hpp>
#include <list>

namespace book
{
    class Team
    {
        public:
            Team(const Team&) = delete;
            Team& operator=(const Team&) = delete;

            Team(sf::RenderWindow& window,int id,const sf::Color& color=sf::Color::White);

            void addGold(int amount);
            void addEnemy(Team* team);
            const std::list<Team*>& getEnemies()const;
            void setQgId(std::uint32_t);
            std::uint32_t getQgId();

            int id()const;

            bool isAlive;
            TeamGui gui;

        private:
            int _id;
            int _points;
            int _gold;
            std::uint32_t _QGId;

            std::list<Team*> _enemies;


    };
}
#endif
