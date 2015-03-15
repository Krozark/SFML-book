#ifndef BOOK_CONFIGURATION_HPP
#define BOOK_CONFIGURATION_HPP

#include <SFML/Graphics.hpp> //Texture
#include <SFML/Audio.hpp> //SoundBuffer

#include <SFML-Book/ResourceManager.hpp> //ResourceManager
#include <SFML-Book/ActionMap.hpp> //ActionMap

//#define BOOK_DEBUG
namespace book
{
    class Player;
    class Configuration
    {
        public:
            Configuration() = delete;
            Configuration(const Configuration&) = delete;
            Configuration& operator=(const Configuration&) = delete;

            enum Fonts : int {Gui};
            static ResourceManager<sf::Font,int> fonts;

            enum PlayerInputs : int {
                TurnLeft,
                TurnRight,
                MoveLeft,
                MoveRight,
                HardDrop,
            };
            static ActionMap<int> playerInputs;

            enum Sounds : int {
                Spawn,
                Explosion,
                LevelUp,
            };
            static ResourceManager<sf::SoundBuffer,int> sounds;


            enum Musics : int {
                Theme
            };
            static ResourceManager<sf::Music,int> musics;


            static void initialize();

        private:
            static void initTextures();
            static void initFonts();
            static void initSounds();
            static void initMusics();

            static void initPlayerInputs();
    };
}
#endif
