#ifndef BOOK_SHOOT_HPP
#define BOOK_SHOOT_HPP

#include <SFML-Book/Entity.hpp>

namespace book
{
    class Shoot : public Entity
    {
        public:
            Shoot(const Shoot&) = delete;
            Shoot& operator=(const Shoot&) = delete;
            Shoot(Configuration::Textures textures, World& world);
            using Entity::Entity;

            virtual void update(sf::Time deltaTime);

        protected:
            sf::Time            _duration;
    };


    class ShootPlayer : public Shoot
    {
        public :
            ShootPlayer(const ShootPlayer&) = delete;
            ShootPlayer& operator=(const ShootPlayer&) = delete;

            ShootPlayer(Player& from);
            virtual bool isCollide(const Entity& other)const;
    };

    class SmallSaucer;
    class ShootSaucer : public Shoot
    {
        public :
            ShootSaucer(const ShootSaucer&) = delete;
            ShootSaucer& operator=(const ShootSaucer&) = delete;

            ShootSaucer(SmallSaucer& from);
            virtual bool isCollide(const Entity& other)const;
    };
}
#endif
