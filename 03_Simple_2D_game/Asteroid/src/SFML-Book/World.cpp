#include <SFML-Book/World.hpp>
#include <SFML-Book/Entity.hpp>

namespace book
{
    World::World(float x,float y): _x(x),
    _y(y)
    {
    }

    World::~World()
    {
        for(Entity* entity :_entities)
            delete entity;
        _entities.clear();
    }

    void World::add(Entity* entity)
    {
        _entities.push_back(entity);
    }

    void World::remove(Entity* entity)
    {

    }

    void World::update(sf::Time deltaTime)
    {
        for(Entity* entity_ptr : _entities)
        {
            Entity& entity = *entity_ptr;

            entity.update(deltaTime);

            sf::Vector2f pos = entity.getPosition();

            if(pos.x < 0)
            {
                pos.x = _x;
                pos.y = _y - pos.y;
            }
            else if (pos.x > _x)
            {
                pos.x = 0;
                pos.y = _y - pos.y;
            }

            if(pos.y < 0)
                pos.y = _y;
            else if(pos.y > _y)
                pos.y = 0;

            entity.setPosition(pos);
        }
    }

    void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(Entity* entity : _entities)
            target.draw(*entity,states);
    }
}
