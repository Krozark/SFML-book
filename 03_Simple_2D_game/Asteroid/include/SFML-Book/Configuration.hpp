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
                PlayerLife,
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

            enum Fonts : int {Gui};
            static ResourceManager<sf::Font,int> fonts;

            enum PlayerInputs : int {Up,
                Left,
                Right,
                Shoot,
            };
            static ActionMap<int> player_inputs;

            static void initialize();

            static int level;
            static int lives;

            static void addScore(int s);
            static int getScore();

            static book::Player* player;

            static void draw(sf::RenderTarget& target);

        private:
            static int _score;
            static sf::Text   _txt_score;
            static sf::Sprite _spr_life;

            static void initTextures();
            static void initFonts();

            static void initPlayerInputs();
    };
}
#endif
