#include <SFML-Book/gui/Button.hpp>

namespace book
{
    namespace gui
    {
        Button::FuncType Button::defaultFunc = [](const sf::Event&,Button&)->void{};

        Button::Button(Layout* parent) : Widget(parent), on_click(defaultFunc)
        {
        }

        bool Button::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)
        {
            bool res = false;
            if(event.type == sf::Event::MouseButtonReleased)
            {
                const sf::Vector2f pos = _position + parent_pos;
                const sf::Vector2f size = getSize();
                sf::FloatRect rect;

                rect.left = pos.x;
                rect.top = pos.y;
                rect.width = size.x;
                rect.height = size.y;

                if(rect.contains(event.mouseButton.x,event.mouseButton.y))
                {
                    on_click(event,*this);
                    res = true;
                }
            }
            return res;
        }
    }
}
