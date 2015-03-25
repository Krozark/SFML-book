#include <SFML-utils/gui/SpriteButton.hpp>

#include <SFML-utils/gui/Configuration.hpp>

namespace sfutils
{
    namespace gui
    {
        
        SpriteButton::SpriteButton(const sf::Texture& tex,Widget* parent) : Widget(parent),Button(parent), Sprite(tex,parent)
        {
            _color = sf::Color::White;
            updateShape();
        }

        SpriteButton::~SpriteButton()
        {
        }

        void SpriteButton::setColor(const sf::Color& color)
        {
            _color = color;
            Sprite::setColor(color);
        }

        void SpriteButton::onMouseEntered()
        {
            const float light = Configuration::Colors::lighting;

            Sprite::setColor(sf::Color(_color.r*light,
                                          _color.b*light,
                                          _color.b*light));
        }

        void SpriteButton::onMouseLeft()
        {
            SpriteButton::setColor(_color);
        }

        void SpriteButton::updateShape()
        {
            Button::updateShape();
            //Sprite::updateShape(); //usless because not override
        }
        void SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            Sprite::draw(target,states);
        }
    }
}
