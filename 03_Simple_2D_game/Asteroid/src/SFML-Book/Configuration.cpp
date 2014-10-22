#include <SFML-Book/Configuration.hpp>

namespace book
{
    ResourceManager<sf::Texture,int> Configuration::textures;
    ActionMap<int> Configuration::player_inputs;

    void Configuration::initialize()
    {
        initTextures();
        initPlayerInputs();
    }

    void Configuration::initTextures()
    {
        textures.load(Textures::Player,"media/Player/Ship.png");
    }

    void Configuration::initPlayerInputs()
    {
        player_inputs.map(PlayerInputs::Up,Action(sf::Keyboard::Up));
        player_inputs.map(PlayerInputs::Right,Action(sf::Keyboard::Right));
        player_inputs.map(PlayerInputs::Left,Action(sf::Keyboard::Left));
    }
}
