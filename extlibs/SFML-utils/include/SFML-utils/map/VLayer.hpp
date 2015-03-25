#ifndef SFUTILS_MAP_VLAYER_HPP
#define SFUTILS_MAP_VLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace sfutils
{
    namespace map
    {
        class VLayer
        {
            public:
                VLayer(const VLayer&) = delete;
                VLayer& operator=(const VLayer&) = delete;

                VLayer(const std::string& type,int z=0,bool isStatic=false);
                virtual ~VLayer();
                virtual void sort() = 0;

                int z()const;
                const std::string& getType()const;

                bool isStatic()const;

            protected:
                const bool _isStatic;

                sf::RenderTexture _renderTexture;
                sf::Sprite _sprite;
                sf::FloatRect _lastViewport;

                const std::string _type;

            private:
                friend class VMap;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states,const sf::FloatRect& viewport) = 0;

                const int _z;
        };
    }
}
#endif
