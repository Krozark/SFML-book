#include <SFML-Book/Entity.hpp>

namespace book
{
    Entity::Entity(Configuration::Textures tex_id,World& world) : _world(world),_alive(true)
    {
        sf::Texture& texture = Configuration::textures.get(tex_id);
        _sprite.setTexture(texture);
        _sprite.setOrigin(texture.getSize().x/2.f,texture.getSize().y/2.f);
    }
    
    Entity::~Entity()
    {
    }

    bool Entity::isAlive()const
    {
        return _alive;
    }

    const sf::Vector2f& Entity::getPosition()const
    {
        return _sprite.getPosition();
    }
    
    void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(_sprite,states);
    }

    void Entity::onDestroy()
    {
        _alive = false;
    }
}
