#include <SFML-Book/Entity.hpp>
#include <SFML-Book/Component.hpp>

ES_INIT_ENTITY(book::Entity);

namespace book
{
    Entity::Entity(sfutils::EntityManager<Entity>* manager,std::uint32_t id) : sfutils::Entity<Entity>(manager,id), onHit(nullptr), onHitted(nullptr)
    {
        name = "???";
    }

    sf::Vector2f Entity::getPosition()const
    {
        return component<CompSkin>()->_sprite.getPosition();
    }

    void Entity::setPosition(const sf::Vector2f& pos)
    {
        component<CompSkin>()->_sprite.setPosition(pos);
    }

    void Entity::draw(sf::RenderTarget& target,sf::RenderStates states)const
    {
        target.draw(component<CompSkin>()->_sprite,states);

        CompHp::Handle hp = component<CompHp>();
        if(hp.isValid())
        {
            hp->draw(target,states);
        }
    }
}
