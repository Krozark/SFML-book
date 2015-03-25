#ifndef SFUTILS_MAP_LAYER_HPP
#define SFUTILS_MAP_LAYER_HPP

#include <SFML-utils/map/VLayer.hpp>
#include <list>

namespace sfutils
{
    namespace map
    {
        template<typename CONTENT>
        class Layer : public VLayer
        {
            public:
                Layer(const Layer&) = delete;
                Layer& operator=(const Layer&) = delete;

                Layer(const std::string& type,int z=0,bool isStatic=false);
                virtual ~Layer();

                CONTENT* add(const CONTENT& content,bool resort=true);
                CONTENT* add(CONTENT&& content,bool resort=true);

                std::list<CONTENT*> getByCoords(const sf::Vector2i& coords,const VMap& map);

                bool remove(const CONTENT* content_ptr,bool resort=true);

                virtual void sort() override;

                

            private:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) override;

                std::list<CONTENT> _content;

        };

        template<typename CONTENT>
        class Layer<CONTENT*> : public VLayer
        {
            public:
                Layer(const Layer&) = delete;
                Layer& operator=(const Layer&) = delete;

                Layer(const std::string& type,int z=0,bool isStatic=false);
                virtual ~Layer();

                CONTENT* add(CONTENT* content,bool resort=true);

                std::list<CONTENT*> getByCoords(const sf::Vector2i& coords,const VMap& map);

                bool remove(const CONTENT* content_ptr,bool resort=true);

                virtual void sort() override;

            private:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) override;

                std::list<CONTENT*> _content;

        };
    }
}
#include <SFML-utils/map/Layer.tpl>
#endif
