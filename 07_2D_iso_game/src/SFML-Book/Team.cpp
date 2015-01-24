#include <SFML-Book/Team.hpp>

namespace book
{
    Team::Team(int id,const sf::Color& color) : _id(id), _color(color), _points(0), _gold(0)
    {
    }
}
