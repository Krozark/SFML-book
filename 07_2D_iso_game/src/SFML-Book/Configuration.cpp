#include <SFML-Book/Configuration.hpp>
#include <SFML-utils/gui/Configuration.hpp>

namespace book
{
    sfutils::ResourceManager<sf::Texture,int> Configuration::textures;
    sfutils::ResourceManager<sfutils::Animation,int> Configuration::animations;
    sfutils::ActionMap<int> Configuration::gui_inputs;

    void Configuration::initialize()
    {
        initGuiConfiguration();
        initTextures();
        initAnimations();
        initInputs();
    }

    void Configuration::setGuiColor(const sf::Color& color)
    {
        sfutils::gui::Configuration::Colors::button_fill = color;;
        sfutils::gui::Configuration::Colors::button_outline = sf::Color(color.r*1.4,
                                                                     color.g*1.4,
                                                                     color.b*1.4,
                                                                     color.a);
        sfutils::gui::Configuration::Colors::label_text = sf::Color(color.r*0.3,
                                                                     color.g*0.3,
                                                                     color.b*0.3,
                                                                     color.a);
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

    void Configuration::initGuiConfiguration()
    { 
        //setGuiColor(sf::Color(170,200,80));
        //sfutils::gui::Configuration::Colors::lighting = 1.4;
        //unsigned int Configuration::Sizes::button_outline_thickness = 5;
        //unsigned int Configuration::Sizes::layout_spacing = 10;
    }
}
