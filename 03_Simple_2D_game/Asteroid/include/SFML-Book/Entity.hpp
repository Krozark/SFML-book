#ifndef BOOK_ENTITY_HPP
#define BOOK_ENTITY_HPP

#include <SFML/Graphics.hpp> //Drawable, Sprite
#include <SFML-Book/Configuration.hpp> //Configuration

namespace book
{
    class Entity :  public sf::Drawable 
    {
        public:
            Entity(const Entity&) = delete;
            Entity& operator=(const Entity&) = delete;

            Entity(Configuration::Textures tex_id);

            virtual ~Entity();

            virtual bool isCollide(const Entity& other)const = 0;

            const sf::Vector2f& getPosition()const;

            template<typename ... Args>
            void setPosition(Args&& ... args);

            virtual void update(sf::Time deltaTime) = 0;

        protected:
            sf::Sprite          _sprite;

        private :
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}
#include <SFML-Book/Entity.tpl>
#endif
