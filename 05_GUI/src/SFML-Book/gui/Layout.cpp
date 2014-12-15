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
    }
}
