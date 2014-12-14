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

                Button(const std::string& text,Layout* parent=nullptr);

                void setText(const std::string& text);
                void setCharacterSize(unsigned int size);
                void setTextColor(const sf::Color& color);

                void setFillColor(const sf::Color& color);
                void setOutlineColor(const sf::Color& color);
                void setOutlineThickness(float thickness);

                
                FuncType on_click;

                virtual sf::Vector2f getSize()const override;

            protected:
                virtual void processEvent(const sf::Event& event)override;

            private:
                sf::Text _text;
                sf::RectangleShape _shape;

                void updateShape();
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
