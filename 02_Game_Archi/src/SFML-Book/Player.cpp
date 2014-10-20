#include <SFML-Book/Player.hpp>
#include <cmath> //sin, cos

namespace book
{
    Player::Player() : _shape(sf::Vector2f(32,32))
                       ,_is_moving(false)
                       ,_rotation(0)
    {
        _shape.setFillColor(sf::Color::Blue);
        _shape.setOrigin(16,16);

        bind(Action(sf::Keyboard::Up),[this](const sf::Event&){
             _is_moving = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        });

        bind(Action(sf::Keyboard::Left),[this](const sf::Event&){
             _rotation-= sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
         });

        bind(Action(sf::Keyboard::Right),[this](const sf::Event&){
             _rotation+= sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
         });
    }
    
    void Player::processEvents()
    {
        _rotation = 0;
        ActionTaget::processEvents();
    }

    void Player::update(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();

        if(_rotation != 0)
        {
            float angle = _rotation*180*seconds;
            _shape.rotate(angle);
        }
        
        if(_is_moving)
        { 
            float angle = _shape.getRotation() / 180 * M_PI - M_PI / 2;
            _velocity += sf::Vector2f(std::cos(angle),std::sin(angle)) * 60.f * seconds;
        }

        _shape.move(seconds * _velocity);
    }

   void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
       target.draw(_shape,states);
   }
}
