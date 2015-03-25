#ifndef SFUTILS_MAP_TILE_HPP
#define SFUTILS_MAP_TILE_HPP

#include <SFML/Graphics.hpp>

namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        class Tile : public sf::Drawable
        {
            public:
                Tile(const Tile&) = delete;
                Tile& operator=(const Tile&) = delete;

                Tile(Tile&&) = default;
                Tile& operator=(Tile&&) = default;

                //convert pixel to word coord 
                static sf::Vector2i mapPixelToCoords(float x,float y,float scale);
                static sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos,float scale);
                
                //return the center of the tile position in pixel relative to the openGL world
                static sf::Vector2f mapCoordsToPixel(int x,int y,float scale);
                static sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos,float scale);

                Tile(int pos_x,int pos_y,float scale);
                
                template< typename ...Args>
                inline void setFillColor(Args&& ... args);

                template< typename ...Args>
                void setPosition(Args&& ... args);

                sf::Vector2f getPosition()const;

                template< typename ...Args>
                void setCoords(Args&& ... args);

                void setTexture(const sf::Texture *texture,bool resetRect=false);
                void setTextureRect(const sf::IntRect& rect);

                sf::FloatRect getGlobalBounds()const;
                sf::FloatRect getLocalBounds()const;


            private:
                sf::ConvexShape _shape;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#include <SFML-utils/map/Tile.tpl>
#endif
