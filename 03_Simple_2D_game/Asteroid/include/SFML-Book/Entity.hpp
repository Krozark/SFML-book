#ifndef BOOK_ENTITY_HPP
#define BOOK_ENTITY_HPP

#include <SFML/Graphics.hpp> //Drawable, Sprite
#include <SFML-Book/Configuration.hpp> //Configuration

namespace book
{
    class World;
    class Entity :  public sf::Drawable 
    {
        public:
            Entity(const Entity&) = delete;
            Entity& operator=(const Entity&) = delete;

            Entity(Configuration::Textures tex_id,World& world);

            virtual ~Entity();

            virtual bool isAlive()const;

            const sf::Vector2f& getPosition()const;

            template<typename ... Args>
            void setPosition(Args&& ... args);

            virtual bool isCollide(const Entity& other)const = 0;

            virtual void update(sf::Time deltaTime) = 0;

            virtual void onDestroy();


        protected:
            friend class Meteor;
            friend class Player;
            friend class Saucer;
            friend class ShootPlayer;
            friend class ShootSaucer;
            sf::Sprite          _sprite;

            sf::Vector2f        _impulse;

            World& _world;

            bool _alive;

        private :
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}
#include <SFML-Book/Entity.tpl>
#endif
