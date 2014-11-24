#ifndef BOOK_WORLD_HPP
#define BOOK_WORLD_HPP

#include <SFML/Graphics.hpp> //Drawable

#include <Box2D/Box2D.h>

namespace book
{
    class Piece;
    class World : public sf::Drawable
    {
        public:
            World(const World&) = delete;
            World& operator=(const World&) = delete;

            World(int size_x,int size_y);
            ~World();

            void update(sf::Time deltaTime);
            void update_physics(sf::Time deltaTime);

            Piece* newPiece();

        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            b2World _physical_world;

            void create_wall(int pos_x, int pos_y, int size_x, int size_y);


            const int _x;
            const int _y;
    };
}
#endif
