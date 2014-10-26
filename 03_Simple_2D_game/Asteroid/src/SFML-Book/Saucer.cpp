#include <SFML-Book/Saucer.hpp>
#include <SFML-Book/random.hpp>

namespace book
{
    bool Saucer::isCollide(const Entity& other)const
    {
        return false;
    }

    void Saucer::update(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();

        //float angle = _sprite.getRotation() / 180 * M_PI - M_PI / 2;
        //sf::Vector2f impulse = sf::Vector2f(std::cos(angle),std::sin(angle)) * 300.f;
        //_sprite.move(seconds * impulse);
        
        _sprite.move(seconds * sf::Vector2f(300,0));
    }

    Saucer* Saucer::newSaucer()
    {
        Saucer* res = nullptr;
        if(random(0,1) < Configuration::score - 40000)
          res = new SmallSaucer;
        else
          res = new BigSaucer;
        return res;
    }

    /************ BigSaucer ******************/

    BigSaucer::BigSaucer() : Saucer(Configuration::Textures::BigSaucer)
    {
    }

    int BigSaucer::getPoints()const
    {
        return 50;
    }

    /********** SmallSaucer *********************/

    SmallSaucer::SmallSaucer() : Saucer(Configuration::Textures::SmallSaucer)
    {
    }

    int SmallSaucer::getPoints()const
    {
        return 200;
    }

    void SmallSaucer::update(sf::Time deltaTime)
    {
        Saucer::update(deltaTime);
        //shoot on the player
    }

}
