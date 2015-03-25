#ifndef SFUTILS_ES_APPLICATION_HPP
#define SFUTILS_ES_APPLICATION_HPP

#include <SFML-utils/es/Entity.hpp>
#include <SFML-utils/es/System.hpp>

namespace sfutils
{
    namespace es
    {
        template<typename ENTITY>
        class Application
        {
            public:
                Application(const Application&) = delete;
                Application& operator=(const Application&) = delete;

                Application();

                void update(sf::Time deltaTime);

                EntityManager<ENTITY> entities;
                SystemManager<ENTITY> systems;
        };
    }
}
#include <SFML-utils/es/Application.tpl>
#endif
