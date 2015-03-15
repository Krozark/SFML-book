#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Window.hpp>

#include <SFML-Book/World.hpp>
#include <SFML-Book/ActionTarget.hpp>
#include <SFML-Book/Stats.hpp>

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
            void update(const sf::Time& deltaTime,const sf::Time& timePerFrame);
            void update_physics(const sf::Time& deltaTime,const sf::Time& timePerFrame); //< do some updates
            void render();//< draw all the stuff

            sf::RenderWindow _window; //< the window use to display the game

            int _moveDirection;
            int _rotateDirection;
            
            Piece* _currentPiece;

            World _world;

            Stats _stats;

            sf::Time timeSinceLastFall;
    };
}

#endif
