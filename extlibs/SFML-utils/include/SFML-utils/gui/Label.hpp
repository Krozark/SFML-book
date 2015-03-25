#ifndef SMFL_UTILS_GUI_LABEL_HPP
#define SMFL_UTILS_GUI_LABEL_HPP

#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        class Label : virtual public Widget
        {
            public:
                Label(const Label&) = delete;
                Label& operator=(const Label&) = delete;

                Label(const std::string& text,Widget* parent=nullptr);
                Label(const std::string& text,sf::Font& font,Widget* parent=nullptr);

                virtual ~Label();

                void setText(const std::string& text);
                void setCharacterSize(unsigned int size);
                unsigned int getCharacterSize()const;
                void setTextColor(const sf::Color& color);

                virtual sf::Vector2f getSize()const override;

            private:
                sf::Text _text;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
