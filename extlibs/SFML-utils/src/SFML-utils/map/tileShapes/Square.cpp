#include <SFML-utils/map/tileShapes/Square.hpp>
#include <cmath>

namespace sfutils
{
    namespace geometry
    {
        sf::ConvexShape Square::_shape;
        Square::__Initiatiser Square::__initiatiser__;

        const float height = 2;

        const sf::ConvexShape& Square::getShape()
        {
            return _shape;
        }

        sf::Vector2f Square::mapCoordsToPixel(int X,int Y,float scale)
        {
            return sf::Vector2f(X*scale*height,
                                Y*scale*height);
        }

        sf::Vector2i Square::mapPixelToCoords(float X,float Y,float scale)
        {
            return round(X/scale/height,
                         Y/scale/height);
        }

        sf::Vector2i Square::round(float x, float y)
        {
            return sf::Vector2i(x+0.5,y+0.5);
        }

        sf::IntRect Square::getTextureRect(int x,int y,float scale)
        {
            sf::Vector2f pos = mapCoordsToPixel(x,y,scale);
            sf::IntRect res(pos.x,
                          pos.y,
                          height * scale,
                          height * scale);
            return res;
        }

        int Square::distance(int x1,int y1, int x2,int y2)
        {
            float x = x1 - x2;
            x = x*x;

            float y = y1 - y2;
            y = y*y;

                return ceil(sqrt(x + y));
          }

        void Square::init()
        {
            _shape.setPointCount(4);
            _shape.setPoint(0,sf::Vector2f(0,0));
            _shape.setPoint(1,sf::Vector2f(0,height));
            _shape.setPoint(2,sf::Vector2f(height,height));
            _shape.setPoint(3,sf::Vector2f(height,0));

            _shape.setOrigin(height/2,height/2);
        }
        
    }
}
