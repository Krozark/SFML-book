#ifndef BOOK_GUI_TEXTBUTTON_HPP
#define BOOK_GUI_TEXTBUTTON_HPP

#include <SFML-Book/gui/Button.hpp>

namespace book
{
    namespace gui
    {
        class TextButton : public Button
        {
            public:
                TextButton(const TextButton&) = delete;
                TextButton& operator=(const TextButton&) = delete;

                TextButton(const std::string& text, Layout* parent=nullptr);

                virtual ~TextButton();

                void setText(const std::string& text);
                void setCharacterSize(unsigned int size);
                void setTextColor(const sf::Color& color);

                void setFillColor(const sf::Color& color);
                void setOutlineColor(const sf::Color& color);
                void setOutlineThickness(float thickness);

                virtual sf::Vector2f getSize()const override;

            private:
                sf::Text _text;
                sf::RectangleShape _shape;

                void updateShape()override;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
