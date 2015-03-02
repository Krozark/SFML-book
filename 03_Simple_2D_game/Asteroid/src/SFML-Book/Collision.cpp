#include <SFML-Book/Collision.hpp>
#include <cmath>

namespace book
{
    bool Collision::circleTest(const sf::Sprite& first, const sf::Sprite& second)
    {
        sf::Vector2f first_rect(first.getTextureRect().width,first.getTextureRect().height);
        first_rect.x *= first.getScale().x;
        first_rect.y *= first.getScale().y;

        sf::Vector2f second_rect(second.getTextureRect().width,second.getTextureRect().height);
        second_rect.x *= second.getScale().x;
        second_rect.y *= second.getScale().y;

        float radius1 = (first_rect.x + first_rect.y) / 4;
        float radius2 = (second_rect.x + second_rect.y) / 4;

        float xd = first.getPosition().x - second.getPosition().x;
        float yd = first.getPosition().y - second.getPosition().y;

        return std::sqrt(xd * xd + yd * yd) <= radius1 + radius2;
    }
}
