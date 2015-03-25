#ifndef SFUTILS_MAP_MAP_HPP
#define SFUTILS_MAP_MAP_HPP


#include <SFML-utils/map/VMap.hpp>
#include <SFML-utils/map/Layer.hpp>
#include <SFML-utils/map/Tile.hpp>


namespace sfutils
{
    namespace map
    {
        template<typename GEOMETRY>
        class Map : public VMap
        {
            public:
                Map(const Map&) = delete;
                Map& operator=(const Map&) = delete;

                Map(float size);

                void loadFromJson(const utils::json::Object& root) override;

                virtual sf::Vector2i mapPixelToCoords(float x,float y) const override;
                
                virtual sf::Vector2f mapCoordsToPixel(int x,int y) const override;

                virtual const sf::ConvexShape getShape()const override;

                virtual std::list<sf::Vector2i> getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const override;
                virtual sf::Vector2i getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const override;
                virtual int getDistance(const sf::Vector2i& origin, const sf::Vector2i& dest) const override;
        };
    }
}
#include <SFML-utils/map/Map.tpl>
#endif
