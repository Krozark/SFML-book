#include <SFML-Book/Meteor.hpp>
#include <SFML-Book/random.hpp>
#include <SFML-Book/World.hpp>
#include <SFML-Book/Collision.hpp>

namespace book
{
    bool Meteor::isCollide(const Entity& other)const
    {
        //not a meteor
        if(dynamic_cast<const Meteor*>(&other) == nullptr)
        {
            return Collision::circleTest(_sprite,other._sprite);
        }
        return false;
    }

    Meteor::Meteor(Configuration::Textures textures, World& world) :Enemy(textures, world){

	}
	
    void Meteor::update(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();
        _sprite.move(seconds * _impulse);
    }

    /****************** BigMeteor *********************/
    BigMeteor::BigMeteor(World& world) : Meteor((Configuration::Textures)book::random(Configuration::Textures::BigMeteor1,Configuration::Textures::BigMeteor4),world)
    {
        _impulse *= 100.f;
    }

    int BigMeteor::getPoints()const
    {
        return 20;
    }

    void BigMeteor::onDestroy()
    {
        Meteor::onDestroy();
        
        int nb = book::random(2,3);
        for(int i=0;i<nb;++i)
        {
            MediumMeteor* meteor = new MediumMeteor(_world);
            meteor->setPosition(getPosition());
            _world.add(meteor);
        }
        _world.add(Configuration::Sounds::Explosion1);
    }

    /************ MediumMeteor ****************/

    MediumMeteor::MediumMeteor(World& world) : Meteor((Configuration::Textures)book::random(Configuration::Textures::MediumMeteor1,Configuration::Textures::MediumMeteor2),world)
    {
        _impulse *= 200.f;
    }

    int MediumMeteor::getPoints()const
    {
        return 60;
    }

    void MediumMeteor::onDestroy()
    {
        Meteor::onDestroy();
        
        int nb = book::random(2,3);
        for(int i=0;i<nb;++i)
        {
            SmallMeteor* meteor = new SmallMeteor(_world);
            meteor->setPosition(getPosition());
            _world.add(meteor);
        }
        _world.add(Configuration::Sounds::Explosion2);
    }

    /************ SmallMeteor ****************/

    SmallMeteor::SmallMeteor(World& world) : Meteor((Configuration::Textures)book::random(Configuration::Textures::SmallMeteor1,Configuration::Textures::SmallMeteor4),world)
    {
        _impulse *= 300.f;
    }

    int SmallMeteor::getPoints()const
    {
        return 100;
    }

    void SmallMeteor::onDestroy()
    {
        Meteor::onDestroy();
        _world.add(Configuration::Sounds::Explosion3);
    }

}
