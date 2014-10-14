#include <SFML-Book/Player.hpp>
#include <cmath>

namespace book
{
    Player::Player() : _shape(sf::Vector2f(32,32))
    {
        _shape.setFillColor(sf::Color::Blue);
        _shape.setOrigin(16,16);
    }

    void Player::addSpeed()
    {
        float angle = _shape.getRotation() / 180 * M_PI - M_PI / 2;

        _velocity += sf::Vector2f(std::cos(angle),std::sin(angle)) * 5.f;
    }

    void Player::rotate(float angle)
    {
        _shape.rotate(angle);
    }

    void Player::update(sf::Time deltaTime)
    {
        _shape.move(deltaTime.asSeconds() * _velocity);
    }

   void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
       target.draw(_shape,states);
   }
}
