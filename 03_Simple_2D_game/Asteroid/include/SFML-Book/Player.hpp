#ifndef BOOK_PLAYER_HPP
#define BOOK_PLAYER_HPP

#include <SFML-Book/ActionTarget.hpp> //ActionTarget
#include <SFML-Book/Entity.hpp> //Entity

namespace book
{
    class Player : public Entity , public ActionTarget<int>
    {
        public:
            Player(const Player&) = delete;
            Player& operator=(const Player&) = delete;

            Player(World& world);

            virtual bool isCollide(const Entity& other)const;
            virtual void update(sf::Time deltaTime);

            void processEvents();

            void shoot();

            virtual void onDestroy();

        private:

            sf::Vector2f        _velocity;

            bool _is_moving;
            int _rotation;

            sf::Time            _time_since_last_shoot;
    };
}
#endif
