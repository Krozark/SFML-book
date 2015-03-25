
namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        inline sf::Vector2i Tile<GEOMETRY>::mapPixelToCoords(float x,float y,float scale)
        {
            return GEOMETRY::mapPixelToCoords(x,y,scale);
        }

        template<typename GEOMETRY>
        inline sf::Vector2i Tile<GEOMETRY>::mapPixelToCoords(const sf::Vector2f& pos,float scale)
        {
            return GEOMETRY::mapPixelToCoords(pos.x,pos.y,scale);
        }

        template<typename GEOMETRY>
        inline sf::Vector2f Tile<GEOMETRY>::mapCoordsToPixel(int x,int y,float scale)
        {
            return GEOMETRY::mapCoordsToPixel(x,y,scale);
        }

        template<typename GEOMETRY>
        inline sf::Vector2f Tile<GEOMETRY>::mapCoordsToPixel(const sf::Vector2i& pos,float scale)
        {
            return GEOMETRY::mapCoordsToPixel(pos.x,pos.y,scale);
        }

        template<typename GEOMETRY>
        Tile<GEOMETRY>::Tile(int pos_x,int pos_y,float scale)
        {
            _shape = GEOMETRY::getShape();

            _shape.setOutlineColor(sf::Color(255,255,255,25));
            _shape.setOutlineThickness(2.f/scale);

            _shape.setScale(scale,scale);

            setCoords(pos_x,pos_y);
        }

        template<typename GEOMETRY>
        template< typename ...Args>
        inline void Tile<GEOMETRY>::setFillColor(Args&& ... args)
        {
            _shape.setFillColor(std::forward<Args&>(args)...);
        }

        template<typename GEOMETRY>
        template< typename ...Args>
        inline void Tile<GEOMETRY>::setPosition(Args&& ... args)
        {
            _shape.setPosition(args...);
        }

        template<typename GEOMETRY>
        template< typename ...Args>
        inline void Tile<GEOMETRY>::setCoords(Args&& ... args)
        {
            sf::Vector2f pos = mapCoordsToPixel(args...,_shape.getScale().x);
            _shape.setPosition(pos);
        }

        template<typename GEOMETRY>
        inline sf::Vector2f Tile<GEOMETRY>::getPosition()const
        {
            return _shape.getPosition();
        }

        template<typename GEOMETRY>
        inline void Tile<GEOMETRY>::setTexture(const sf::Texture *texture,bool resetRect)
        {
            _shape.setTexture(texture,resetRect);
        }

        template<typename GEOMETRY>
        inline void Tile<GEOMETRY>::setTextureRect(const sf::IntRect& rect)
        {
            _shape.setTextureRect(rect);
        }

        template<typename GEOMETRY>
        inline sf::FloatRect Tile<GEOMETRY>::getGlobalBounds()const
        {
            return _shape.getGlobalBounds();
        }

        template<typename GEOMETRY>
        inline sf::FloatRect Tile<GEOMETRY>::getLocalBounds()const
        {
            return _shape.getLocalBounds();
        }

        template<typename GEOMETRY>
        inline void Tile<GEOMETRY>::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(_shape,states);
        }
    }
}
