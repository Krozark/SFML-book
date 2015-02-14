#include <SFML-Book/server/Entity.hpp>

ES_INIT_ENTITY(book::Entity);

namespace book
{
    Entity::Entity(sfutils::EntityManager<Entity>* manager,std::uint32_t id) : sfutils::Entity<Entity>(manager,id), onHit(nullptr), onHitted(nullptr)
    {
    }

    sf::Vector2f Entity::getPosition()const
    {
        return _position;
    }

    sf::Vector2i Entity::getCoord()const
    {
        return _coords;
    }

    void Entity::setType(short int type)
    {
        _type = type;
    }

    short int Entity::getType()const
    {
        return _type;
    }

    void Entity::setPosition(const sf::Vector2f& pos, const sf::Vector2i& coord)
    {
        _position = pos;
        _coords = coord;
    }

}
