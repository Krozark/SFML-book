#include <SFML-Book/Saucer.hpp>

#include <SFML-Book/random.hpp> //random
#include <SFML-Book/World.hpp> //World
#include <SFML-Book/Meteor.hpp> //Meteor
#include <SFML-Book/Shoot.hpp> //ShootSaucer
#include <SFML-Book/Collision.hpp> //Collision
#include <SFML-Book/Player.hpp> //Player

#include  <cfloat>

namespace book
{
    bool Saucer::isCollide(const Entity& other)const
    {
        if(dynamic_cast<const ShootSaucer*>(&other) == nullptr)
        {
            return Collision::circleTest(_sprite,other._sprite);
        }
        return false;
    }
    Saucer::Saucer(Configuration::Textures textures, World& world) :Enemy(textures, world){

	}

    void Saucer::update(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();

        //get the nearest object
        Entity* near = nullptr;
        float near_distance = 300;
        
        for(Entity* entity_ptr : _world.getEntities())
        {
            if(entity_ptr != this and(dynamic_cast<const Meteor*>(entity_ptr) or dynamic_cast<const ShootPlayer*>(entity_ptr)))
            {
                float x = getPosition().x - entity_ptr->getPosition().x;
                float y = getPosition().y - entity_ptr->getPosition().y;

                float dist = std::sqrt(x*x + y*y);
                if(dist < near_distance)
                {
                    near_distance = dist;
                    near = entity_ptr;
                }
            }
        }

        if(near != nullptr)
        {
            sf::Vector2f pos = near->getPosition() - getPosition();

            float angle_rad = std::atan2(pos.y,pos.x);
            _impulse -= sf::Vector2f(std::cos(angle_rad),std::sin(angle_rad)) * 300.f * seconds;
        }
        else
        {
            sf::Vector2f pos = Configuration::player->getPosition() - getPosition();

            float angle_rad = std::atan2(pos.y,pos.x);
            _impulse += sf::Vector2f(std::cos(angle_rad),std::sin(angle_rad)) * 100.f * seconds;
        }

        _sprite.move(seconds * _impulse);
    }
    void Saucer::onDestroy()
    {
        Enemy::onDestroy();
        _world.add(Configuration::Sounds::Boom2);
    }

    void Saucer::newSaucer(World& world)
    {
        Saucer* res = nullptr;
        if(book::random(0.f,1.f) > Configuration::getScore()/ 40000.f)
            res = new BigSaucer(world);
        else
            res = new SmallSaucer(world);

        res->setPosition(random(0,1)*world.getX(),random(0.f,(float)world.getY()));
        world.add(res);
    }

    /************ BigSaucer ******************/

    BigSaucer::BigSaucer(World& world) : Saucer(Configuration::Textures::BigSaucer,world)
    {
        _world.add(Configuration::Sounds::SaucerSpawn1);
        _impulse *= 300.f;
    }

    int BigSaucer::getPoints()const
    {
        return 50;
    }

    /********** SmallSaucer *********************/

    SmallSaucer::SmallSaucer(World& world) : Saucer(Configuration::Textures::SmallSaucer,world)
    {        
        _timeSinceLastShoot = sf::Time::Zero;
        _world.add(Configuration::Sounds::SaucerSpawn2);
        _impulse *= 400.f;
    }

    int SmallSaucer::getPoints()const
    {
        return 200;
    }

    void SmallSaucer::update(sf::Time deltaTime)
    {
        Saucer::update(deltaTime);
        //shoot on the Configuration::player
        _timeSinceLastShoot += deltaTime;
        if(_timeSinceLastShoot > sf::seconds(1.5))
        {
            if(Configuration::player != nullptr)
                _world.add(new ShootSaucer(*this));
            _timeSinceLastShoot = sf::Time::Zero;
        }
    }

}
