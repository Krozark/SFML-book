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
            const sf::Color& getColor()const;

            bool processEvent(sf::Event& event);
            void processEvents();
            void draw(sf::RenderTarget& target);

        private:
            int _id;
            int _points;
            int _gold;

            TeamGui _gui;

    };
}
#endif
