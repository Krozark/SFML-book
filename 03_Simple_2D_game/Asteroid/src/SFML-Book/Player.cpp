#include <SFML-Book/Player.hpp>
#include <cmath> //sin, cos

#include <SFML-Book/Configuration.hpp> //Configuration

namespace book
{
    Player::Player() : Entity(Configuration::Textures::Player)
                       ,ActionTarget(Configuration::player_inputs)
                       ,_is_moving(false)
                       ,_rotation(0)
    {
        bind(Configuration::PlayerInputs::Up,[this](const sf::Event&){
             _is_moving = true;
        });

        bind(Configuration::PlayerInputs::Left,[this](const sf::Event&){
             _rotation-= 1;
         });

        bind(Configuration::PlayerInputs::Right,[this](const sf::Event&){
             _rotation+= 1;
         });
    }

    bool Player::isCollide(const Entity& other)const
    {
        return false;
    }

    void Player::shoot()const
    {
    }

    void Player::processEvents()
    {
        _is_moving = false;
        _rotation = 0;
        ActionTarget::processEvents();
    }

    void Player::update(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();

        if(_rotation != 0)
        {
            float angle = _rotation*180*seconds;
            _sprite.rotate(angle);
        }
        
        if(_is_moving)
        { 
            float angle = _sprite.getRotation() / 180 * M_PI - M_PI / 2;
            _velocity += sf::Vector2f(std::cos(angle),std::sin(angle)) * 300.f * seconds;
        }

        _sprite.move(seconds * _velocity);
    }
}
