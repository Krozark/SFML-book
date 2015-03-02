#include <SFML-Book/client/Team.hpp>

namespace book
{
    Team::Team(int id,const sf::Color& color) : _id(id), _color(color)
    {
    }

    int Team::id()const
    {
        return _id;
    }

    const sf::Color& Team::getColor()const
    {
        return _color;
    }
}
