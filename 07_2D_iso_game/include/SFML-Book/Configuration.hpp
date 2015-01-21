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
                Eye
            };

            static sfutils::ResourceManager<sf::Texture,int> textures;

            enum Animations: int {
                EyeLeft,
                EyeRight
            };

            static sfutils::ResourceManager<sfutils::Animation,int> animations;

            static void initialize();

        private:

            static void initTextures();
            static void initAnimations();
    };
}
#endif
