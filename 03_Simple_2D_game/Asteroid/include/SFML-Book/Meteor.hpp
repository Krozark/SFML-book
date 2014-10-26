#ifndef BOOK_METEOR_HPP
#define BOOK_METEOR_HPP

#include <SFML-Book/Enemy.hpp>

namespace book
{
    class Meteor : public Enemy
    {
        public:
            Meteor(const Meteor&) = delete;
            Meteor& operator=(const Meteor&) = delete;

            Meteor(Configuration::Textures tex_id,World& world);

            virtual bool isCollide(const Entity& other)const;
            virtual void update(sf::Time deltaTime);

        protected:
            sf::Vector2f        _impulse;
            
    };

    class BigMeteor : public Meteor
    {
        public :
            BigMeteor(World& world);
            virtual int getPoints()const;
            virtual void onDestroy();
    };

    class MediumMeteor : public Meteor
    {
        public :
            MediumMeteor(World& worll);
            virtual int getPoints()const;
            virtual void onDestroy();
    };

    class SmallMeteor : public Meteor
    {
        public :
            SmallMeteor(World& world);
            virtual int getPoints()const;
    };
}
#endif
