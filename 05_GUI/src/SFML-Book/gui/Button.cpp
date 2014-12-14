#include <SFML-Book/gui/Button.hpp>
#include <SFML-Book/Configuration.hpp>

namespace book
{
    namespace gui
    {
        Button::FuncType Button::defaultFunc = [](const sf::Event&,Button&)->void{};

        Button::Button(const std::string& text,Layout* parent) : Widget(parent), on_click(defaultFunc)
        {
            _text.setFont(Configuration::fonts.get(Configuration::Fonts::Gui));
            setFillColor(sf::Color(50,50,50));
            setOutlineThickness(5);
            setOutlineColor(sf::Color(128,128,128));

            setText(text);
            setTextColor(sf::Color(128,128,128));
        }

        void Button::setText(const std::string& text)
        {
            _text.setString(text);
            updateShape();
        }

        void Button::setCharacterSize(unsigned int size)
        {
            _text.setCharacterSize(size);
            updateShape();
        }

        void Button::setTextColor(const sf::Color& color)
        {
            _text.setColor(color);
        }

        void Button::setFillColor(const sf::Color& color)
        {
            _shape.setFillColor(color);
        }

        void Button::setOutlineColor(const sf::Color& color)
        {
            _shape.setOutlineColor(color);
        }

        void Button::setOutlineThickness(float thickness)
        {
            _shape.setOutlineThickness(thickness);
        }

        sf::Vector2f Button::getSize()const
        {
            sf::FloatRect rect = _shape.getGlobalBounds();
            return sf::Vector2f(rect.width,rect.height);
        }

        void Button::processEvent(const sf::Event& event)
        {
            if(event.type == sf::Event::MouseButtonReleased)
            {
                sf::FloatRect rect = _shape.getGlobalBounds();
                sf::Vector2f pos = getGlobalPosition();
                rect.left += pos.x;
                rect.top += pos.y;
                if(rect.contains(event.mouseButton.x,event.mouseButton.y))
                    on_click(event,*this);
            }
        }

        void Button::updateShape()
        {
            sf::FloatRect rect = _text.getLocalBounds();
            unsigned int char_size = _text.getCharacterSize();
            _shape.setSize(sf::Vector2f(char_size*2 + rect.width,char_size*2 + rect.height));
            _text.setPosition(char_size,char_size);

            //_size = _shape.getSize();
        }

        void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform.translate(_position);
            target.draw(_shape,states);
            target.draw(_text,states);
        }

    }
}
