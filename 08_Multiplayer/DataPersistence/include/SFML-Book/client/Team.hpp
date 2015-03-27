#ifndef BOOK_TEAM_HPP
#define BOOK_TEAM_HPP

#include <vector>
#include <list>
#include <cstdint>

#include <SFML/Graphics.hpp>

namespace book
{
    class Client;

    class Team
    {
        public:
            Team(const Team&) = delete;
            Team& operator=(const Team&) = delete;

            Team(Team&&) = default;
            Team& operator=(Team&&) = default;

            Team(int id,const sf::Color& color);

            int id()const;
            const sf::Color& getColor()const;

            bool isAlive;

        private:
            const int _id;
            sf::Color _color;

    };
}
#endif
