#ifndef BOOK_TEAM_HPP
#define BOOK_TEAM_HPP

#include <SFML/Graphics.hpp>

namespace book
{
    class Team
    {
        public:
            Team(const Team&) = delete;
            Team& operator=(const Team&) = delete;

            Team(int id,const sf::Color& color=sf::Color::White);

        private:
            int _id;
            sf::Color _color;
            int _points;
            int _gold;
    };
}
#endif
