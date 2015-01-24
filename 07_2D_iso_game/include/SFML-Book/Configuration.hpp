#ifndef BOOK_CONFIGURATION_HPP
#define BOOK_CONFIGURATION_HPP

#include <SFML/Graphics.hpp>

#include <SFML-utils/Core.hpp>

namespace book
{
    class Configuration
    {
        public:
            Configuration() = delete;

            enum Textures : int {
                TexMain,
                //WormsEgg,
                //Worm1,
                //Worm2,
                //Worm3,
                //EyeEgg,
                TexEye
            };

            static sfutils::ResourceManager<sf::Texture,int> textures;

            enum Animations: int {
                AnimMain,
                AnimEyeLeft,
                AnimEyeRight
            };

            static sfutils::ResourceManager<sfutils::Animation,int> animations;

            static void initialize();

        private:

            static void initTextures();
            static void initAnimations();
    };
}
#endif
