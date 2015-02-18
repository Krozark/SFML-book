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

            void goToHyperspace();

            virtual void onDestroy();

        private:

            bool _isMoving;
            int _rotation;

            sf::Time            _timeSinceLastShoot;
    };
}
#endif
