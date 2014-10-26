#include <SFML-Book/Enemy.hpp>

namespace book
{
    void Enemy::onDestroy()
    {
        Entity::onDestroy();
        Configuration::score += getPoints();
    }
}
