#include <SFML-Book/Entity.hpp>

namespace book
{
    Entity::Entity(sfutils::EntityManager<Entity>* manager,std::uint32_t id,sfutils::Animation* animation) : sfutils::Entity<Entity>(manager,id)
    {
    }

    //TODO
    sf::Vector2i Entity::getPosition()const
    {
        return {0,0};
    }
    void Entity::draw(sf::RenderTarget& target,sf::RenderStates states)const
    {
    }
}
