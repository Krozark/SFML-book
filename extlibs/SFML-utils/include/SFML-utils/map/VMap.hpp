#ifndef SFUTILS_MAP_VMAP_HPP
#define SFUTILS_MAP_VMAP_HPP

#include <SFML-utils/map/VLayer.hpp>
#include <string>
#include <utils/json/Driver.hpp>

#include <SFML-utils/core/ResourceManager.hpp>
#include <list>

namespace sfutils
{
    namespace map
    {
        class VMap
        {
            public:
                VMap(const VMap&) = delete;
                VMap& operator=(const VMap&) = delete;

                VMap(float size);
                virtual ~VMap();

                virtual void loadFromJson(const utils::json::Object& root) = 0;
                bool loadFromFile(const std::string& filename);
                bool loadFromStream(std::istream& in);

                void add(VLayer* layer,bool sort=true);
                void remove(VLayer* layer);
                void remove(size_t index);

                size_t size()const;
                VLayer* at(size_t index)const;
                void clear();

                float getTileSize()const;

                virtual sf::Vector2i mapPixelToCoords(float x,float y) const = 0;
                sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const;
                
                virtual sf::Vector2f mapCoordsToPixel(int x,int y) const =0;
                sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos) const;

                virtual const sf::ConvexShape getShape()const = 0;

                virtual std::list<sf::Vector2i> getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const = 0;
                virtual sf::Vector2i getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const =0;
                virtual int getDistance(const sf::Vector2i& origin, const sf::Vector2i& dest)const = 0;

                static VMap* createMapFromFile(const std::string& filename);
                static VMap* createMapFromStream(std::istream& in);


            protected:
                void sortLayers();
                const float _tileSize;
                
                ResourceManager<sf::Texture,std::string> _textures;
                
            private:
                friend class MapViewer;
                void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) const;
                std::vector<VLayer*> _layers;
        };

    }
}
#endif
