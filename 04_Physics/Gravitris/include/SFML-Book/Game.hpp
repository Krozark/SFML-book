#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Window.hpp>

#include <SFML-Book/World.hpp>
#include <SFML-Book/ActionTarget.hpp>

namespace book
{
    class Piece;
    class Game: public ActionTarget<int>
    {
        public:
            //not capyable class
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            Game(int x,int y,int word_x=10,int word_y=20); //< constuctor

            void run(int minimum_frame_per_seconds=30,int phyiscs_frame_per_seconds=60);

        private:

            void processEvents();//< Process events
            void update_physics(const sf::Time& deltaTime); //< do some updates
            void render();//< draw all the stuff

            sf::RenderWindow _window; //< the window use to display the game
            Piece* _current_piece;

            World _world;
    };
}
#endif
