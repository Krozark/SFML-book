#ifndef BOOK_PLAYER_HPP
#define BOOK_PLAYER_HPP

#include <SFML/Graphics.hpp>


namespace book
{
    class Player : public sf::Drawable
    {
        public:
            Player(const Player&) = delete;
            Player& operator=(const Player&) = delete;

            Player();

            template<typename ... Args>
            void setPosition(Args&& ... args);

            void addSpeed();

            void rotate(float angle);
            
            void update(sf::Time deltaTime);

        protected:

        private:
             virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            sf::RectangleShape  _shape;
            sf::Vector2f        _velocity;
    };
}
#include <SFML-Book/Player.tpl>
#endif
