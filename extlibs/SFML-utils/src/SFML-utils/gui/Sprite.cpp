#include <SFML-utils/gui/Sprite.hpp>

namespace sfutils
{
    namespace gui
    {
        Sprite::Sprite(const sf::Texture& tex,Widget* parent) : Widget(parent), _sprite(tex)
        {
            _color = _sprite.getColor();
            updateShape();
        }

        Sprite::~Sprite()
        {
        }

        void Sprite::setTexture(const sf::Texture& texture,bool resetRect)
        {
            _sprite.setTexture(texture,resetRect);
            updateShape();
        }
        void Sprite::setTextureRect(const sf::IntRect& rectangle)
        {
            _sprite.setTextureRect(rectangle);
        }

        void Sprite::setColor(const sf::Color& color)
        {
            _color = color;
            _sprite.setColor(color);
        }

        sf::Vector2f Sprite::getSize()const
        {
            sf::FloatRect rect = _sprite.getGlobalBounds();
            return sf::Vector2f(rect.width,rect.height);
        }

        void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform.translate(_position);
            target.draw(_sprite,states);
        }
    }
}
