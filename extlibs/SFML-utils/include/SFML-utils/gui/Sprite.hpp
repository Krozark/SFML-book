#ifndef SFUTILS_GUI_SPRITE_HPP
#define SFUTILS_GUI_SPRITE_HPP

#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        class Sprite : virtual public Widget
        {
            public:
                Sprite(const Sprite&) = delete;
                Sprite& operator=(const Sprite&) = delete;

                Sprite(const sf::Texture& tex,Widget* parent=nullptr);
                virtual ~Sprite();

                void setTexture(const sf::Texture& texture,bool resetRect=false);
                void setTextureRect(const sf::IntRect& rectangle);
                virtual void setColor(const sf::Color& color);

                virtual sf::Vector2f getSize()const override;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            private:
                sf::Sprite _sprite;
                sf::Color _color;
        };
    }
}
#endif
