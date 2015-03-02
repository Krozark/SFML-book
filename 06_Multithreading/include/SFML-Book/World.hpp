#ifndef BOOK_WORLD_HPP
#define BOOK_WORLD_HPP

#include <list>

#include <SFML/Graphics.hpp> //Drawable

#include <Box2D/Box2D.h>

#include <SFML-Book/DebugDraw.hpp>
#include <SFML-Book/Configuration.hpp>

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

#ifdef BOOK_DEBUG
            void displayDebug();
#endif
            int clearLines(bool& del,const Piece& current);

            void updateGravity(int level);
            void add(Configuration::Sounds sound_id);            

            bool isGameOver()const;

            void reset();

        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            b2World _physical_world;
#ifdef BOOK_DEBUG
            DebugDraw _debugDraw;
#endif

            void create_wall(int pos_x, int pos_y, int size_x, int size_y);

            const int _x;
            const int _y;

            std::list<std::unique_ptr<sf::Sound>> _sounds;

    };
}
#endif
