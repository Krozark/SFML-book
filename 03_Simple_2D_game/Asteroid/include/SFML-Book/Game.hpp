#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML-Book/Player.hpp>
#include <SFML-Book/Saucer.hpp>
#include <SFML-Book/World.hpp>

/**
 * \brief namespace for the book
 */
namespace book
{
    /**
     * \brief A class to manage the game
     */
    class Game
    {
        public:
            //non copyable class
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            Game(int X=800, int Y=600); //< constructor

            void run(int minimum_frame_per_seconds=30);

            void initLevel();

        private:

            void processEvents();//< Process events
            void update(sf::Time deltaTime); //< do some updates
            void render();//< draw all the stuff

            sf::RenderWindow _window; //< the window use to display the game
            World _world;
            



    };
}
#endif
