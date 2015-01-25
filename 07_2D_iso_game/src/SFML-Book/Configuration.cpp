#include <SFML-Book/Configuration.hpp>

namespace book
{
    sfutils::ResourceManager<sf::Texture,int> Configuration::textures;
    sfutils::ResourceManager<sfutils::Animation,int> Configuration::animations;
    sfutils::ActionMap<int> Configuration::gui_inputs;

    void Configuration::initialize()
    {
        initTextures();
        initAnimations();
        initInputs();
    }

    void Configuration::initTextures()
    {
        textures.load(TexMain,"media/skins/main.png");
        textures.load(TexWormEgg,"media/skins/wormegg.png");
        textures.load(TexWormEggBirth,"media/skins/wormegg-birth.png");
        textures.load(TexWorm,"media/skins/worm.png");
        textures.load(TexEye,"media/skins/eye.png");
    }


    void Configuration::initAnimations()
    {
        //QG
        animations.load(AnimMainStand,&textures.get(TexMain)).addFramesLine(5,1,0);
        //Worm Egg
        animations.load(AnimWormEggStand,&textures.get(TexWormEgg)).addFramesLine(4,1,0);
        animations.load(AnimWormEggBirth,&textures.get(TexWormEggBirth)).addFramesLine(2,1,0);
        //worm
        animations.load(AnimWormLeft,&textures.get(TexWorm)).addFramesLine(3,2,0);
        animations.load(AnimWormRight,&textures.get(TexWorm)).addFramesLine(3,2,1);
        //Eye
        animations.load(AnimEyeLeft,&textures.get(TexEye)).addFramesLine(4,2,0);
        animations.load(AnimEyeRight,&textures.get(TexEye)).addFramesLine(4,2,1);
    }

    void Configuration::initInputs()
    {
        gui_inputs.map(GuiInputs::Escape,sfutils::Action(sf::Keyboard::Escape,sfutils::Action::Type::Pressed));
    }
}
