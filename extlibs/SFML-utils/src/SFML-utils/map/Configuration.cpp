#include <SFML-utils/map/Configuration.hpp>

namespace sfutils
{
namespace map {
    ActionMap<int> Configuration::defaultMapInputs;
    Configuration::__Initiatiser Configuration::__initiatiser__;

    void Configuration::initEvents()
    {
        defaultMapInputs.map(MapInputs::MoveUp,Action(sf::Keyboard::Up));
        defaultMapInputs.map(MapInputs::MoveDown,Action(sf::Keyboard::Down));
        defaultMapInputs.map(MapInputs::MoveLeft,Action(sf::Keyboard::Left));
        defaultMapInputs.map(MapInputs::MoveRight,Action(sf::Keyboard::Right));
    }

    void Configuration::init()
    {
        initEvents();
    }
}
}
