#ifndef BOOK_LEVEL_HPP
#define BOOK_LEVEL_HPP

#include <string>
#include <functional>

#include <SFML/Graphics.hpp>

#include <SFML-utils/es/Application.hpp>
#include <SFML-utils/Map.hpp>

#include <SFML-Book/Entity.hpp>
#include <SFML-Book/Configuration.hpp>


namespace book
{
    class Level : private sfutils::Application<Entity>
    {
        public:
            using GEOMETRY = sfutils::HexaIso;

            Level(const Level&) = delete;
            Level& operator=(const Level&) = delete;

            Level(sf::RenderWindow& window,const std::string& filename);
            ~Level();

            void update(sf::Time deltaTime);

            bool processEvent(sf::Event& event);
            void processEvents();
            void draw(sf::RenderTarget& window);

            struct Param {
                explicit Param(sf::Vector2i&,
                               Entity&,
                               sfutils::Layer<GEOMETRY,Entity*>&,
                               sfutils::VMap&);

                sf::Vector2i& coord;
                Entity& entity;
                sfutils::Layer<GEOMETRY,Entity*>& layer;
                sfutils::VMap& map;
            };

            using FuncType = std::function<void(Param& param)>;
            static FuncType defaultFunc;

            FuncType onPickup;

            sfutils::EntityManager<Entity>& entityManager();
            sfutils::Layer<GEOMETRY,sf::ConvexShape>& getHighlightLayer()const;
            const sf::ConvexShape getShape()const;

            
            Entity& createEntity(const sf::Vector2i& coord);
            void createSound(Configuration::Sounds sound_id,const sf::Vector2i& coord);
            void createSound(Configuration::Sounds sound_id,const sf::Vector2f& pos);

            sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos)const;
            sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos)const;

            sf::Vector2i mapCoordsToScreen(const sf::Vector2i& pos)const;
            sf::Vector2i mapScreenToCoords(const sf::Vector2i& pos)const;

            std::list<Entity*> getByCoords(const sf::Vector2i& coord)const;

            std::list<sf::Vector2i> getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const;
            sf::Vector2i getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const;
            int getDistance(const sf::Vector2i& origin,const sf::Vector2i& dest)const;

            sf::Vector2i getMinCoord()const;
            sf::Vector2i getMaxCoord()const;

        private:
            friend class Game;

            sfutils::VMap* _map;
            sfutils::MapViewer _viewer;

            sf::ConvexShape* _mouse_light;
            sfutils::Layer<GEOMETRY,sf::ConvexShape>* _mouse_layer;
            sfutils::Layer<GEOMETRY,Entity*>* _entites_layer;

            std::list<std::unique_ptr<sf::Sound>> _sounds;
            sf::Listener _listener;
    };
}
#endif
