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

            void run(int frame_per_seconds=60);

        private:

            void processEvents();
            void update(sf::Time deltaTime);
            void render();

            void initTeam(Team* team,const sf::Vector2i& pos);

            sf::RenderWindow _window;
            sf::Sprite _cursor;
            
            Level* _level;
            int _team_id;
            Team*_team[2];

            Level::FuncType onPickup;
    };
}
#endif
