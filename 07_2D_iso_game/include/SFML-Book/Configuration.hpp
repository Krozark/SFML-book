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
                TexWormEgg,
                TexWormEggBirth,
                TexWorm,
                //Worm2,
                //Worm3,
                //EyeEgg,
                TexEye
            };

            static sfutils::ResourceManager<sf::Texture,int> textures;

            enum Animations: int {
                AnimMainStand,
                AnimWormEggStand,
                AnimWormEggBirth,
                AnimWormLeft,
                AnimWormRight,
                AnimEyeLeft,
                AnimEyeRight,
            };

            static sfutils::ResourceManager<sfutils::Animation,int> animations;

            enum GuiInputs : int {
                Escape
            };
            static sfutils::ActionMap<int> gui_inputs;


            static void initialize();
            static void setGuiColor(const sf::Color& color);

        private:

            static void initTextures();
            static void initAnimations();
            static void initInputs();

            static void initGuiConfiguration();
    };
}
#endif
