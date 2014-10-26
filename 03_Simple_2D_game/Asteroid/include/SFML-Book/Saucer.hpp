#ifndef BOOK_SAUCER_HPP
#define BOOK_SAUCER_HPP

#include <SFML-Book/Enemy.hpp>

namespace book
{
    class Saucer : public Enemy
    {
        public:
            Saucer(const Saucer&) = delete;
            Saucer& operator=(const Saucer&) = delete;

            using Enemy::Enemy;

            virtual bool isCollide(const Entity& other)const;

            static Saucer* newSaucer();
            
            virtual void update(sf::Time deltaTime);

        private:
    };

    class BigSaucer : public Saucer
    {
        public:
            BigSaucer();
            virtual int getPoints()const;
    };

    class SmallSaucer : public Saucer
    {
        public :
            SmallSaucer();
            virtual int getPoints()const;
            virtual void update(sf::Time deltaTime);
    };

}
#endif
