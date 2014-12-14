#include <SFML-Book/gui/Layout.hpp>

#include <SFML-Book/gui/Widget.hpp>

namespace book
{
    namespace gui
    {
        Layout::Layout(Widget* parent): _parent(parent)
        {
        }

        Layout::~Layout()
        {
        }

        sf::Vector2f Layout::getGlobalPosition()const
        {
            sf::Vector2f res;
            if(_parent)
                res += _parent->getGlobalPosition();
            return res;
        }
    }
}
