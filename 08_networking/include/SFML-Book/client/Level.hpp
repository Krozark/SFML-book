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

            Level(sf::RenderWindow& window,std::istream& stream);
            ~Level();

            void update(sf::Time deltaTime);

            bool processEvent(sf::Event& event);
            void processEvents();
            void processNetworkEvent(packet::NetworkEvent* msg);
            void draw(sf::RenderTarget& window);

            /*struct Param {
                explicit Param(sf::Vector2i&,
                               Entity&,
                               sfutils::Layer<Entity*>&,
                               sfutils::VMap&);

                sf::Vector2i& coord;
                Entity& entity;
                sfutils::Layer<Entity*>& layer;
                sfutils::VMap& map;
            };

            using FuncType = std::function<void(Param& param)>;
            static FuncType defaultFunc;

            FuncType onPickup;

            sfutils::EntityManager<Entity>& entityManager();*/
            sfutils::Layer<sf::ConvexShape>& getHighlightLayer()const;
            const sf::ConvexShape getShape()const;

            
            /*
            void destroyEntity(Entity& e);
            */

            void createSound(Configuration::Sounds sound_id,const sf::Vector2i& coord);
            void createSound(Configuration::Sounds sound_id,const sf::Vector2f& pos);

           /* sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos)const;
            sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos)const;

            sf::Vector2i mapCoordsToScreen(const sf::Vector2i& pos)const;
            sf::Vector2i mapScreenToCoords(const sf::Vector2i& pos)const;

            std::list<Entity*> getByCoords(const sf::Vector2i& coord);

            std::list<sf::Vector2i> getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const;
            sf::Vector2i getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const;
            int getDistance(const sf::Vector2i& origin,const sf::Vector2i& dest)const;*/

            sf::Vector2i getMinCoord()const;
            sf::Vector2i getMaxCoord()const;

        private:
            friend class Game;

            sfutils::VMap* _map;
            sfutils::MapViewer _viewer;

            std::unordered_map<sf::Vector2i,std::list<Entity*>> _byCoords;

            sf::ConvexShape* _mouse_light;
            sfutils::Layer<sf::ConvexShape>* _mouse_layer;
            sfutils::Layer<Entity*>* _entities_layer;

            std::list<std::unique_ptr<sf::Sound>> _sounds;

            std::unordered_map<int,Team> _teamInfo;

            Entity& createEntity(unsigned int id,const sf::Vector2i& coord);

            void destroyEntity(std::uint32_t id);
            void setPosition(Entity& e,const sf::Vector2i& old,const sf::Vector2i& n);
    };
}
#endif
