#ifndef BOOK_WORLD_HPP
#define BOOK_WORLD_HPP

#include <SFML/Graphics.hpp> //Drawable
#include <SFML/Audio.hpp> //Drawable
#include <list> //list
#include <memory>

#include <SFML-Book/Configuration.hpp>

namespace book
{
    class Entity;
    class World : public sf::Drawable
    {
        public:
            World(const World&) = delete;
            World& operator=(const World&) = delete;

            World(float x,float y);
            ~World();

            void update(sf::Time deltaTime);

            void add(Entity* entity);

            void clear();

            void add(Configuration::Sounds sound_id);

            bool isCollide(const Entity& other);

            int size();

            int getX()const;
            int getY()const;

            const std::list<Entity*> getEntities()const;

        private:
            std::list<Entity*>  _entities; 
            std::list<Entity*>  _entitiesTmp; 
            std::list<std::unique_ptr<sf::Sound>> _sounds;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            const int _x;
            const int _y;
    };
}
#endif
