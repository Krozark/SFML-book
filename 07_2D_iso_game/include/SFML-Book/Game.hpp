#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <SFML-Book/Team.hpp>
#include <SFML-Book/Level.hpp>

namespace book
{
    class Game
    {
        public:
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            Game(int X=1600, int Y=900);
            ~Game();

            bool load(const std::string& level);

            void run(int minimum_frame_per_seconds=30);

        private:

            void processEvents();
            void update(sf::Time deltaTime);
            void render();

            sf::RenderWindow _window;
            
            Level* _level;
            Team* _team;

            Level::FuncType onPickup;
    };
}
#endif
