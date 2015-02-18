#ifndef BOOK_LEVEL_HPP
#define BOOK_LEVEL_HPP

#include <string>
#include <functional>

#include <SFML/Graphics.hpp>

#include <SFML-utils/es/Application.hpp>
#include <SFML-utils/Map.hpp>

#include <SFML-Book/common/Configuration.hpp>
#include <SFML-Book/common/Packet.hpp>

#include <SFML-Book/client/Entity.hpp>
#include <SFML-Book/client/Team.hpp>
#include <SFML-Book/common/std_hash.hpp>


namespace book
{
    class Level : private sfutils::Application<Entity>
    {
        public:
            Level(const Level&) = delete;
            Level& operator=(const Level&) = delete;

            Level(sf::RenderWindow& window,int team,std::istream& stream,const std::string& data);
            ~Level();

            void update(sf::Time deltaTime);

            bool processEvent(sf::Event& event);
            void processEvents();
            void processNetworkEvent(packet::NetworkEvent* msg);
            void draw(sf::RenderTarget& window);


            using FuncType = std::function<void(std::uint32_t id,sf::Vector2i coord)>;
            static FuncType defaultFunc;

            FuncType onPickup;

            sfutils::Layer<sf::ConvexShape>& getHighlightLayer()const;
            const sf::ConvexShape getShape()const;

            sfutils::EntityManager<Entity>& entityManager();

            void createSound(Configuration::Sounds sound_id,const sf::Vector2i& coord);
            void createSound(Configuration::Sounds sound_id,const sf::Vector2f& pos);

            void addEffect(std::function<Effect*(void)> effectFn,const sf::Vector2i& coord);

            sf::Vector2i getMinCoord()const;
            sf::Vector2i getMaxCoord()const;

            sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos)const;
            sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos)const;

            sf::Vector2i mapCoordsToScreen(const sf::Vector2i& pos)const;
            sf::Vector2i mapScreenToCoords(const sf::Vector2i& pos)const;

        private:
            friend class Game;

            sfutils::VMap* _map;
            sfutils::MapViewer _viewer;

            sf::Vector2i _minCoord;
            sf::Vector2i _maxCoord;

            std::unordered_map<sf::Vector2i,std::list<Entity*>> _byCoords;

            sf::ConvexShape* _mouse_light;
            sfutils::Layer<sf::ConvexShape>* _mouseLayer;
            sfutils::Layer<MapComponent*>* _entitiesLayer;
            std::list<Effect*> _effects;

            std::list<std::unique_ptr<sf::Sound>> _sounds;

            std::unordered_map<int,Team> _teamInfo;

            Entity& createEntity(unsigned int id,const sf::Vector2i& coord);

            void destroyEntity(std::uint32_t id);
            void setPosition(Entity& e,const sf::Vector2i& old,const sf::Vector2i& n);
    };
}
#endif
