#include <SFML-Book/Player.hpp>
#include <cmath> //sin, cos

namespace book
{
    Player::Player() : _shape(sf::Vector2f(32,32))
    {
        _shape.setFillColor(sf::Color::Blue);
        _shape.setOrigin(16,16);
        is_moving = false;
        rotation = 0;
    }

    void Player::update(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();

        if(rotation != 0)
        {
            float angle = (rotation>0?1:-1)*180*seconds;
            _shape.rotate(angle);
        }
        
        if(is_moving)
        { 
            float angle = _shape.getRotation() / 180 * M_PI - M_PI / 2;
            _velocity += sf::Vector2f(std::cos(angle),std::sin(angle)) * 30.f * seconds;
        }

        _shape.move(seconds * _velocity);
    }

   void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
       target.draw(_shape,states);
   }
}
