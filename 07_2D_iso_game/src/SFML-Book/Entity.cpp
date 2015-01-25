#include <SFML-Book/Entity.hpp>
#include <SFML-Book/Component.hpp>

ES_INIT_ENTITY(book::Entity);

namespace book
{
    Entity::Entity(sfutils::EntityManager<Entity>* manager,std::uint32_t id, sfutils::Layer<sfutils::HexaIso,Entity*>& layer) : sfutils::Entity<Entity>(manager,id), _layer(layer)
    {
        name = "???";
    }

    void Entity::init()
    {
        add<CompSkin>();
        _layer.add(this);
    }

    Entity::~Entity()
    {
        _layer.remove(this);
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
    }
}
