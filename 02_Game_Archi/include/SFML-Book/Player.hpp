#ifndef BOOK_PLAYER_HPP
#define BOOK_PLAYER_HPP

#include <SFML/Graphics.hpp>

#include <SFML-Book/ActionTarget.hpp> //ActionTarget

namespace book
{
    class Player : public sf::Drawable , public ActionTarget<int>
    {
        public:
            Player(const Player&) = delete;
            Player& operator=(const Player&) = delete;

            Player();

            template<typename ... Args>
            void setPosition(Args&& ... args);

            void processEvents();

            void update(sf::Time deltaTime);

        private:
             virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            sf::Sprite          _ship;
            sf::Vector2f        _velocity;

            bool _is_moving;
            int _rotation;

    };
}
#include <SFML-Book/Player.tpl>
#endif
