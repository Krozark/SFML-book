#ifndef BOOK_CONFIGURATION_HPP
#define BOOK_CONFIGURATION_HPP

#include <SFML/Graphics.hpp> //Texture

#include <SFML-Book/ResourceManager.hpp> //ResourceManager
#include <SFML-Book/ActionMap.hpp> //ActionMap

namespace book
{
    class Player;
    class Configuration
    {
        public:
            Configuration() = delete;
            Configuration(const Configuration&) = delete;
            Configuration& operator=(const Configuration&) = delete;

            enum Textures : int {Player,
                BigSaucer,
                SmallSaucer,
                BigMeteor1,
                BigMeteor2,
                BigMeteor3,
                BigMeteor4,
                MediumMeteor1,
                MediumMeteor2,
                SmallMeteor1,
                SmallMeteor2,
                SmallMeteor3,
                SmallMeteor4,
                ShootPlayer,
                ShootSaucer,
            };

            static ResourceManager<sf::Texture,int> textures;

            enum PlayerInputs : int {Up,
                Left,
                Right,
                Shoot,
            };
            static ActionMap<int> player_inputs;

            static void initialize();

            static int score;
            static int level;
            static int lives;

            static book::Player* player;

        private:

            static void initTextures();

            static void initPlayerInputs();
    };
}
#endif
