#ifndef BOOK_GUI_BUTTON_HPP
#define BOOK_GUI_BUTTON_HPP

#include <SFML-Book/gui/Widget.hpp>
#include <functional>

namespace book
{
    namespace gui
    {
        class Button : public Widget
        {
            public:
                Button(const Button&) = delete;
                Button& operator=(const Button&) = delete;

                using FuncType = std::function<void(const sf::Event& event,Button& self)>;
                static FuncType defaultFunc;

                Button(Layout* parent=nullptr);

                FuncType on_click;

            protected:
                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)override;
        };
    }
}
#endif
