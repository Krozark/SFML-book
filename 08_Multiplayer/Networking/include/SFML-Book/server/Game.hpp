#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <vector>
#include <string>
#include <queue>
#include <set>
#include <unordered_map>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <SFML-utils/es/Application.hpp>
#include <SFML-utils/Map.hpp>

#include <SFML-Book/server/Entity.hpp>

#include <SFML-Book/common/Packet.hpp>
#include <SFML-Book/common/std_hash.hpp>

namespace book
{
    class Team;
    class Client;

    class Game : private sfutils::Application<Entity>
    {
        public:
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            Game(const std::string& mapFileName);
            ~Game();
            
            int getTeamCount();
            int getPalyersCount();

            int id()const;

            bool addClient(Client* client);

            void run();
            void stop();

            Entity& createEntity(const sf::Vector2i& coord,Team* team,MakeAs makeAs);
            void markEntityUpdated(std::uint32_t id);
            void markEntityHit(std::uint32_t id,std::uint32_t enemyId);
            void markEntityHitted(std::uint32_t id,std::uint32_t enemyId);
            void markEntitySpawn(std::uint32_t id);
            void markTeamUpdated(std::uint32_t id);

            void destroyEntity(std::uint32_t id);
            void setPosition(Entity& e,const sf::Vector2i& oldCoord,const sf::Vector2f& oldPos,const sf::Vector2i& newCoord,const sf::Vector2f& newPos);

            sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos)const;
            sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos)const;


            std::list<Entity*> getByCoords(const sf::Vector2i& coord);
            sf::Vector2i getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const;
            int getDistance(const sf::Vector2i& origin,const sf::Vector2i& dest)const;

            using FuncType = std::function<void(Client*)>;
            FuncType onLogOut;


        private:
            bool _isRunning;
            sf::Thread _gameThread;
            sf::Mutex _gameMutex;
            sfutils::VMap* _map;

            std::list<std::uint32_t> _destroyEntityId;
            std::set<std::uint32_t> _updateEntitiesId;
            std::set<std::uint32_t> _updateTeamId;
            std::list<packet::OnHittedEntity::Data> _onHitted;
            std::list<packet::OnHitEntity::Data> _onHit;
            std::set<std::uint32_t> _onSpawn;
            
            packet::CreateEntity _createEntities;
            
            sf::Vector2i _minCoord;
            sf::Vector2i _maxCoord;
            
            sf::Mutex _teamMutex;
            std::vector<Team*> _teams;

            sf::Mutex _clientsMutex;
            std::vector<Client*> _clients;

            void _send();
            sf::Thread _sendThread;
            sf::Mutex _sendMutex;
            std::queue<sf::Packet> _outgoing;


            const int _id;
            static int _numberOfCreations;

            void _run();

            std::string _mapFileName;

            void processNetworkEvents();
            void sendUpdates();

            void update(sf::Time deltaTime);

            void sendToAll(sf::Packet& packet);

            std::unordered_map<sf::Vector2i,std::list<Entity*>> _byCoords;

            // Helpers
            void addUpdate(packet::UpdateEntity& packet,unsigned int id);
            void addCreate(packet::CreateEntity& packet,unsigned int id);
    };
}
#endif
