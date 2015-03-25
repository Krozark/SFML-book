#ifndef SFML_UTILS_GUI_BUTTON_HPP
#define SFML_UTILS_GUI_BUTTON_HPP

#include <SFML-utils/gui/Widget.hpp>
#include <functional>

namespace sfutils
{
    namespace gui
    {
        class Button : virtual public Widget
        {
            public:
                Button(const Button&) = delete;
                Button& operator=(const Button&) = delete;

                using FuncType = std::function<void(const sf::Event& event,Button& self)>;
                static FuncType defaultFunc;

                Button(Widget* parent=nullptr);
                virtual ~Button();

                FuncType on_click;

            protected:
                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)override;

                virtual void onMouseEntered();
                virtual void onMouseLeft();

            private:

                enum Status {
                    Hover = 1
                };
                int _status;
        };
    }
}
#endif
