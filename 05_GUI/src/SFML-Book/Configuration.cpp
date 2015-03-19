#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/random.hpp> //rand_init

namespace book
{
    ResourceManager<sf::Font,int> Configuration::fonts;
    ResourceManager<sf::Music,int> Configuration::musics;
    ResourceManager<sf::SoundBuffer,int> Configuration::sounds;

    ActionMap<int> Configuration::playerInputs;
    ActionMap<int> Configuration::guiInputs;

    void Configuration::initialize()
    {
        initTextures();
        initFonts();
        initSounds();
        initMusics();

        initPlayerInputs();
        initGuiInputs();

        rand_init();

        musics.get(Musics::Theme).setLoop(true);
        musics.get(Musics::Theme).play();

    }

    void Configuration::initTextures()
    {
    }

    void Configuration::initFonts()
    {
        fonts.load(Fonts::Gui,"media/font/trs-million.ttf");
    }

    void Configuration::initSounds()
    {
        sounds.load(Sounds::Spawn,"media/sounds/spawn.flac");
        sounds.load(Sounds::Explosion,"media/sounds/explosion.flac");
        sounds.load(Sounds::LevelUp,"media/sounds/levelup.flac");
    }
    void Configuration::initMusics()
    {
        musics.load(Musics::Theme,"media/musics/theme.ogg");
    }

    void Configuration::initPlayerInputs()
    {
        playerInputs.map(PlayerInputs::TurnRight,Action(sf::Keyboard::Up));
        playerInputs.map(PlayerInputs::TurnLeft,Action(sf::Keyboard::Down));
        playerInputs.map(PlayerInputs::MoveLeft,Action(sf::Keyboard::Left));
        playerInputs.map(PlayerInputs::MoveRight,Action(sf::Keyboard::Right));
        playerInputs.map(PlayerInputs::HardDrop,Action(sf::Keyboard::Space,Action::Type::Released));
    }

    void Configuration::initGuiInputs()
    {
        guiInputs.map(GuiInputs::Escape,Action(sf::Keyboard::Escape,Action::Type::Pressed));
    }
}
