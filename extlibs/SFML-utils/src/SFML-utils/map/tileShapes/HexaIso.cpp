#include <SFML-utils/map/tileShapes/HexaIso.hpp>
#include <cmath>

namespace sfutils
{
    namespace geometry
    {
        sf::ConvexShape HexaIso::_shape;
        HexaIso::__Initiatiser HexaIso::__initiatiser__;

        const float PI = 3.14159265;

        const float sin_75 = sin(75*PI/180);
        const float sin_15 = sin(15*PI/180);
        const float sin_45 = sin(45*PI/180);

        const float height = sin_15+sin_45+sin_75;
        const float delta_x = sin_45-sin_15;
        const float delta_y = sin_75+sin_45;

        const sf::ConvexShape& HexaIso::getShape()
        {
            return _shape;
        }

        sf::Vector2f HexaIso::mapCoordsToPixel(int X,int Y,float scale)
        {
            return sf::Vector2f((Y*delta_x + X*delta_y)*scale,
                                (Y*delta_y/2 + X*delta_x/2)*scale);
        }

        sf::Vector2i HexaIso::mapPixelToCoords(float X,float Y,float scale)
        {
            const float d_x = delta_x * scale;
            const float d_y = delta_y * scale;

            const float y = (-X*d_x + 2*Y*d_y)/(d_y*d_y - d_x*d_x);
            const float x = -(y*d_x - X)/d_y;

            return HexaIso::round(x,y);
        }

        sf::Vector2i HexaIso::round(float x, float y)
        {
            const float z = -y-x;

            float rx = std::round(x);
            float ry = std::round(y);
            float rz = std::round(z);

            const float diff_x = std::abs(rx - x);
            const float diff_y = std::abs(ry - y);
            const float diff_z = std::abs(rz - z);

            if(diff_x > diff_y and diff_x > diff_z)
                rx = -ry-rz;
            else if (diff_y > diff_z)
                ry = -rx-rz;

            return sf::Vector2i(rx,ry);
        }

        sf::IntRect HexaIso::getTextureRect(int x,int y,float scale)
        {
            sf::Vector2f pos = mapCoordsToPixel(x,y,scale);
            sf::IntRect res(pos.x,
                          pos.y,
                          height * scale,
                          height/2 * scale);
            return res;
        }

        int HexaIso::distance(int x1,int y1, int x2,int y2)
        {
                return (std::abs(x1 - x2)
                    + std::abs(y1 - y2)
                    + std::abs((-x1- y1) - (-x2 - y2))) / 2;
          }

        void HexaIso::init()
        {
            _shape.setPointCount(6);
            _shape.setPoint(0,sf::Vector2f(0,(sin_15+sin_75)/2));
            _shape.setPoint(1,sf::Vector2f(sin_15,sin_15/2));
            _shape.setPoint(2,sf::Vector2f(sin_15+sin_75,0));
            _shape.setPoint(3,sf::Vector2f(sin_15+sin_75+sin_45,sin_45/2));
            _shape.setPoint(4,sf::Vector2f(sin_75+sin_45,(sin_75+sin_45)/2));
            _shape.setPoint(5,sf::Vector2f(sin_45,(sin_15+sin_75+sin_45)/2));

            _shape.setOrigin(height/2,height/4);
        }
        
    }
}
