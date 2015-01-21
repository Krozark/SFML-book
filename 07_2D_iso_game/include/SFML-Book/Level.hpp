#ifndef BOOK_LEVEL_HPP
#define BOOK_LEVEL_HPP

#include <string>
#include <SFML/Graphics.hpp>

#include <SFML-utils/Map.hpp>

#include <SFML-Book/Entity.hpp>


namespace book
{
    class Level
    {
        public:
            Level(const Level&) = delete;
            Level& operator=(const Level&) = delete;

            Level(sf::RenderWindow& window,const std::string& filename);
            ~Level();

            void update(sf::Time deltaTime);

            bool processEvent(sf::Event& event);
            void processEvents();

            void draw(sf::RenderWindow& window);


        private:
            sfutils::VMap* _map;
            sfutils::MapViewer _viewer;

            sf::ConvexShape* _mouse_light;
            sfutils::Layer<sfutils::HexaIso,sf::ConvexShape>* _mouse_layer;
            sfutils::Layer<sfutils::HexaIso,Entity*>* _entities_layer;

            sfutils::EntityManager<Entity> _manager;
    };
}
#endif
