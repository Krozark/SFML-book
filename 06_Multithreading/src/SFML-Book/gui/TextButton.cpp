#include <SFML-Book/gui/TextButton.hpp>

namespace book
{
    namespace gui
    {
        TextButton::TextButton(const std::string& text,Widget* parent) : Button(parent), _label(text,this)
        {
            setFillColor(sf::Color(86,20,19));
            setOutlineThickness(5);
            setOutlineColor(sf::Color(146,20,19));
        }

        TextButton::~TextButton()
        {
        }

        void TextButton::setText(const std::string& text)
        {
            _label.setText(text);
        }

        void TextButton::setCharacterSize(unsigned int size)
        {
            _label.setCharacterSize(size);
        }

        void TextButton::setTextColor(const sf::Color& color)
        {
            _label.setTextColor(color);
        }

        void TextButton::setFillColor(const sf::Color& color)
        {
            _fillColor = color;
            _shape.setFillColor(_fillColor);
        }

        void TextButton::setOutlineColor(const sf::Color& color)
        {
            _outlineColor = color;
            _shape.setOutlineColor(_outlineColor);
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
            sf::Vector2f label_size = _label.getSize();
            unsigned int char_size = _label.getCharacterSize();

            _shape.setSize(sf::Vector2f(char_size*2 + label_size.x ,char_size*2 + label_size.y));
            _label.setPosition(char_size,char_size);

            Widget::updateShape();
        }

        void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform.translate(_position);
            target.draw(_shape,states);
            target.draw(_label,states);
        }

        void TextButton::onMouseEntered()
        {
            const float light = 1.4;

            _shape.setOutlineColor(sf::Color(_outlineColor.r*light,
                                             _outlineColor.g*light,
                                             _outlineColor.b*light));
            _shape.setFillColor(sf::Color(_fillColor.r*light,
                                          _fillColor.b*light,
                                          _fillColor.b*light));
        }

        void TextButton::onMouseLeft()
        {
            _shape.setOutlineColor(_outlineColor);
            _shape.setFillColor(_fillColor);
        }
    }
}
