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
                TexCursor,
                TexBuildMain,
                TexBuildWormEgg,
                TexBuildCarnivor,
                //entities
                TexMain,
                TexWormEgg,
                TexWormEggBirth,
                TexWorm,
                TexEye,
                TexCarnivor,
                //effects
                TexBlood1,
                TexBlood2,
                TexBlood3,
                TexBlood4,
                TexFlash,
                TexVoltage,
            };

            static sfutils::ResourceManager<sf::Texture,int> textures;

            enum Animations: int {
                //entities
                AnimMainStand,

                AnimWormEggStand,
                AnimWormEggBirth,
                AnimWormLeft,
                AnimWormRight,

                AnimEyeLeft,
                AnimEyeRight,

                AnimCarnivorStand,
                //effects
                AnimBlood1,
                AnimBlood2,
                AnimBlood3,
                AnimBlood4,
                AnimFlash,
                AnimVoltage,
            };

            static sfutils::ResourceManager<sfutils::Animation,int> animations;

            enum Sounds : int {
                SoundHittedMain,

                SoundHitWorm,
                SoundHittedWorm,
                SoundSpawnWormEgg,

                SoundHitEye,
                SoundHittedEye,
                SoundSpawnEye,

                SoundGold,
            };
            static sfutils::ResourceManager<sf::SoundBuffer,int> sounds;


            enum GuiInputs : int {
                Escape
            };
            static sfutils::ActionMap<int> guiInputs;

            enum MapInputs {
                MoveUp,
                MoveDown,
                MoveLeft,
                MoveRight,
                TakeScreen,
            };

            static sfutils::ActionMap<int> mapInputs;




            static void initialize();
            static void setGuiColor(const sf::Color& color);

        private:

            static void initTextures();
            static void initAnimations();
            static void initInputs();
            static void initSounds();
            static void initEvents();
            
            static void initGuiConfiguration();
    };
}
#endif
