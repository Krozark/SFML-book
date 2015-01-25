#ifndef BOOK_TEAM_HPP
#define BOOK_TEAM_HPP

#include <SFML/Graphics.hpp>
#include <SFML-Book/TeamGui.hpp>

namespace book
{
    class Team
    {
        public:
            Team(const Team&) = delete;
            Team& operator=(const Team&) = delete;

            Team(sf::RenderWindow& window,int id,const sf::Color& color=sf::Color::White);

            void addGold(int amount);

            int id()const;

            TeamGui gui;

        private:
            int _id;
            int _points;
            int _gold;


    };
}
#endif
