#ifndef BOOK_ENEMY_HPP
#define BOOK_ENEMY_HPP

#include <SFML-Book/Entity.hpp> //Entity

namespace book
{
    class Enemy : public Entity
    {
        public:
            Enemy(const Enemy&) = delete;
            Enemy& operator=(const Enemy&) = delete;

            Enemy(Configuration::Textures tex_id,World& world);

            virtual int getPoints()const = 0;

            virtual void onDestroy();

    };
}
#endif
