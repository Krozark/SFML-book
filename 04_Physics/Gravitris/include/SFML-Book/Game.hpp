#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Window.hpp>

#include <SFML-Book/World.hpp>

namespace book
{
    class Game
    {
        public:
            //not capyable class
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            Game(int x,int y); //< constuctor

            void run(int minimum_frame_per_seconds=30,int phyiscs_frame_per_seconds=60);

        private:

            void processEvents();//< Process events
            void update_physics(const sf::Time& deltaTime); //< do some updates
            void render();//< draw all the stuff

            sf::RenderWindow _window; //< the window use to display the game

            World _world;
    };
}
#endif
