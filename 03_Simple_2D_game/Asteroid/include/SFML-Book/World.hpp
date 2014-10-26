#ifndef BOOK_WORLD_HPP
#define BOOK_WORLD_HPP

#include <SFML/Graphics.hpp> //Drawable
#include <list> //list

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
            void remove(Entity* entity);

            int getX()const;
            int getY()const;

        private:
            std::list<Entity*>  _entities; 
            std::list<Entity*>  _entities_tmp; 
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            const int _x;
            const int _y;
    };
}
#endif
