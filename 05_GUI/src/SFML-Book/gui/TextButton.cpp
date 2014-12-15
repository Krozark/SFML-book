#include <SFML-Book/gui/TextButton.hpp>

#include <SFML-Book/Configuration.hpp>

namespace book
{
    namespace gui
    {
        TextButton::TextButton(const std::string& text,Layout* parent) : Button(parent)
        {
            _text.setFont(Configuration::fonts.get(Configuration::Fonts::Gui));
            setFillColor(sf::Color(50,50,50));
            setOutlineThickness(5);
            setOutlineColor(sf::Color(128,128,128));

            setText(text);
            setTextColor(sf::Color(128,128,128));
        }

        TextButton::~TextButton()
        {
        }

        void TextButton::setText(const std::string& text)
        {
            _text.setString(text);
            updateShape();
        }

        void TextButton::setCharacterSize(unsigned int size)
        {
            _text.setCharacterSize(size);
            updateShape();
        }

        void TextButton::setTextColor(const sf::Color& color)
        {
            _text.setColor(color);
        }

        void TextButton::setFillColor(const sf::Color& color)
        {
            _shape.setFillColor(color);
        }

        void TextButton::setOutlineColor(const sf::Color& color)
        {
            _shape.setOutlineColor(color);
        }

        void TextButton::setOutlineThickness(float thickness)
        {
            _shape.setOutlineThickness(thickness);
        }

        sf::Vector2f TextButton::getSize()const
        {
            sf::FloatRect rect = _shape.getGlobalBounds();
            return sf::Vector2f(rect.width,rect.height);
        }
        
        void TextButton::updateShape()
        {
            sf::FloatRect rect = _text.getLocalBounds();
            unsigned int char_size = _text.getCharacterSize();
            _shape.setSize(sf::Vector2f(char_size*2 + rect.width,char_size*2 + rect.height));
            _text.setPosition(char_size,char_size);

            Widget::updateShape();

        }

        void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform.translate(_position);
            target.draw(_shape,states);
            target.draw(_text,states);
        }
    }
}
