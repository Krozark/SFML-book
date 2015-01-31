#include <SFML-Book/Configuration.hpp>
#include <SFML-utils/gui/Configuration.hpp>

#include <SFML-Book/random.hpp>

namespace book
{
    sfutils::ResourceManager<sf::Texture,int> Configuration::textures;
    sfutils::ResourceManager<sfutils::Animation,int> Configuration::animations;
    sfutils::ResourceManager<sf::SoundBuffer,int> Configuration::sounds;
    sfutils::ActionMap<int> Configuration::gui_inputs;
    sfutils::ActionMap<int> Configuration::map_inputs;


    void Configuration::initialize()
    {
        rand_init();
        initGuiConfiguration();

        initTextures();
        initAnimations();
        initInputs();
        initSounds();

        initEvents();
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
        textures.load(TexCursor,"media/gui/cursor.png");
        textures.load(TexBuildWormEgg,"media/gui/wormegg.png");
        //entities
        textures.load(TexMain,"media/skins/main.png");
        textures.load(TexWormEgg,"media/skins/wormegg.png");
        textures.load(TexWormEggBirth,"media/skins/wormegg-birth.png");
        textures.load(TexWorm,"media/skins/worm.png");
        textures.load(TexEye,"media/skins/eye.png");
        //Worm2,
        //Worm3,
        //EyeEgg,
        
        //effects
        textures.load(TexBlood1,"media/effects/blood1.png");
        textures.load(TexBlood2,"media/effects/blood2.png");
        textures.load(TexBlood3,"media/effects/blood3.png");
        textures.load(TexBlood4,"media/effects/blood4.png");

        textures.load(TexFlash,"media/effects/flash.png");
        textures.load(TexVoltage,"media/effects/voltage.png");
    }


    void Configuration::initAnimations()
    {
        //// Entities
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

        ////effects
        animations.load(AnimBlood1,&textures.get(TexBlood1)).addFramesLine(3,2,0).addFramesLine(3,2,1);
        animations.load(AnimBlood2,&textures.get(TexBlood2)).addFramesLine(3,2,0).addFramesLine(3,2,1);
        animations.load(AnimBlood3,&textures.get(TexBlood3)).addFramesLine(3,2,0).addFramesLine(3,2,1);
        animations.load(AnimBlood4,&textures.get(TexBlood4)).addFramesLine(3,2,0).addFramesLine(3,2,1);

        animations.load(AnimFlash,&textures.get(TexFlash)).addFramesLine(3,2,0).addFramesLine(3,2,1);
        animations.load(AnimVoltage,&textures.get(TexVoltage)).addFramesLine(5,2,0).addFramesLine(5,2,1);
    }

    void Configuration::initInputs()
    {
        gui_inputs.map(GuiInputs::Escape,sfutils::Action(sf::Keyboard::Escape,sfutils::Action::Type::Pressed));
    }

    void Configuration::initSounds()
    {
        sf::Listener::setGlobalVolume(100);
        sounds.load(SoundHittedMain,"media/sounds/HittedMain.flac");

        sounds.load(SoundHitWorm,"media/sounds/HitWorm.wav");
        sounds.load(SoundHittedWorm,"media/sounds/HittedWorm.wav");
        sounds.load(SoundSpawnWormEgg,"media/sounds/SpawnWormEgg.flac");

        sounds.load(SoundHitEye,"media/sounds/HitEye.wav");
        sounds.load(SoundHittedEye,"media/sounds/HittedEye.wav");
        sounds.load(SoundSpawnEye,"media/sounds/SpawnEye.wav");
        
        //sounds.load(SoundGold,"media/sounds/Gold.flac");
    }

    void Configuration::initGuiConfiguration()
    { 
        //setGuiColor(sf::Color(170,200,80));
        //sfutils::gui::Configuration::Colors::lighting = 1.4;
        //unsigned int Configuration::Sizes::button_outline_thickness = 5;
        //unsigned int Configuration::Sizes::layout_spacing = 10;
    }

    void Configuration::initEvents()
    {
        map_inputs.map(MapInputs::MoveUp,sfutils::Action(sf::Keyboard::Up));
        map_inputs.map(MapInputs::MoveDown,sfutils::Action(sf::Keyboard::Down));
        map_inputs.map(MapInputs::MoveLeft,sfutils::Action(sf::Keyboard::Left));
        map_inputs.map(MapInputs::MoveRight,sfutils::Action(sf::Keyboard::Right));
        map_inputs.map(MapInputs::TakeScreen,sfutils::Action(sf::Keyboard::F1,sfutils::Action::Released));
    }

}
