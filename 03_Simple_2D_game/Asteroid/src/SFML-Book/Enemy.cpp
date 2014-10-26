#include <SFML-Book/Enemy.hpp>
#include <SFML-Book/random.hpp>

namespace book
{
    Enemy::Enemy(Configuration::Textures tex_id,World& world) : Entity(tex_id,world)
    {
        float angle = book::random(0.f,2.f*M_PI);
        _impulse = sf::Vector2f(std::cos(angle),std::sin(angle));
    }
    
    void Enemy::onDestroy()
    {
        Entity::onDestroy();
        Configuration::addScore(getPoints());
    }
}
