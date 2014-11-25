#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/random.hpp> //rand_init

namespace book
{
    ResourceManager<sf::Font,int> Configuration::fonts;
    ResourceManager<sf::Music,int> Configuration::musics;

    ActionMap<int> Configuration::player_inputs;


    void Configuration::initialize()
    {
        initTextures();
        initFonts();
        initSounds();
        initMusics();

        initPlayerInputs();

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
    }
    void Configuration::initMusics()
    {
        musics.load(Musics::Theme,"media/musics/theme.ogg");
    }

    void Configuration::initPlayerInputs()
    {
        player_inputs.map(PlayerInputs::TurnRight,Action(sf::Keyboard::Up));
        player_inputs.map(PlayerInputs::TurnLeft,Action(sf::Keyboard::Down));
        player_inputs.map(PlayerInputs::MoveLeft,Action(sf::Keyboard::Left));
        player_inputs.map(PlayerInputs::MoveRight,Action(sf::Keyboard::Right));
        player_inputs.map(PlayerInputs::HardDrop,Action(sf::Keyboard::Space,Action::Type::Released));
    }
}
