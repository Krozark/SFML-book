#include <SFML-Book/Player.hpp>
#include <cmath> //sin, cos

#include <SFML-Book/Configuration.hpp> //Configuration
#include <SFML-Book/Collision.hpp> //Collision
#include <SFML-Book/World.hpp> //World
#include <SFML-Book/Shoot.hpp> //ShootPlayer

namespace book
{
    Player::Player(World& world) : Entity(Configuration::Textures::Player,world)
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

        bind(Configuration::PlayerInputs::Shoot,[this](const sf::Event&){
             shoot();
         });
    }

    bool Player::isCollide(const Entity& other)const
    {
        if(dynamic_cast<const ShootPlayer*>(&other) == nullptr)
        {
            return Collision::circleTest(_sprite,other._sprite);
        }
        return false;
    }

    void Player::shoot()
    {
        if(_time_since_last_shoot > sf::seconds(0.3))
        {
            _world.add(new ShootPlayer(*this));
            _time_since_last_shoot = sf::Time::Zero;
        }
    }

    void Player::onDestroy()
    {
        Configuration::player = nullptr;
        _alive = false;
        Configuration::lives--;
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

        _time_since_last_shoot += deltaTime;

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
