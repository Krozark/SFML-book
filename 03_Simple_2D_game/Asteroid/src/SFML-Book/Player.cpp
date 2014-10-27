#include <SFML-Book/Player.hpp>
#include <cmath> //sin, cos

#include <SFML-Book/Configuration.hpp> //Configuration
#include <SFML-Book/Collision.hpp> //Collision
#include <SFML-Book/World.hpp> //World
#include <SFML-Book/Shoot.hpp> //ShootPlayer
#include <SFML-Book/random.hpp> //random

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

        bind(Configuration::PlayerInputs::Hyperspace,[this](const sf::Event&){
             goToHyperspace();
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
            _world.add(Configuration::Sounds::LaserPlayer);
            _time_since_last_shoot = sf::Time::Zero;
        }
    }

    void Player::goToHyperspace()
    {
        _impulse = sf::Vector2f(0,0);
        setPosition(random(0,_world.getX()),random(0,_world.getY()));
        _world.add(Configuration::Sounds::Jump);

    }

    void Player::onDestroy()
    {
        Configuration::player = nullptr;
        _alive = false;
        Configuration::lives--;
        _world.add(Configuration::Sounds::Boom);
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
            float angle = _rotation*250*seconds;
            _sprite.rotate(angle);
        }
        
        if(_is_moving)
        { 
            float angle = _sprite.getRotation() / 180 * M_PI - M_PI / 2;
            _impulse += sf::Vector2f(std::cos(angle),std::sin(angle)) * 300.f * seconds;
        }

        _sprite.move(seconds * _impulse);
    }
}
