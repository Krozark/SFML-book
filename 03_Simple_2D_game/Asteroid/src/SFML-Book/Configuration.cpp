#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Player.hpp> //Player

namespace book
{
    ResourceManager<sf::Texture,int> Configuration::textures;
    ActionMap<int> Configuration::player_inputs;
    int Configuration::score;
    int Configuration::level;
    book::Player* Configuration::player = nullptr;

    void Configuration::initialize()
    {
        score = 0;
        level = 1;
        player = new book::Player;

        initTextures();
        initPlayerInputs();
    }

    void Configuration::initTextures()
    {
        textures.load(Textures::Player,"media/Player/Ship.png");
        //saucers
        textures.load(Textures::BigSaucer,"media/Saucer/Big.png");
        textures.load(Textures::SmallSaucer,"media/Saucer/Small.png");
        //meteors
        //lasers
    }

    void Configuration::initPlayerInputs()
    {
        player_inputs.map(PlayerInputs::Up,Action(sf::Keyboard::Up));
        player_inputs.map(PlayerInputs::Right,Action(sf::Keyboard::Right));
        player_inputs.map(PlayerInputs::Left,Action(sf::Keyboard::Left));
    }
}
