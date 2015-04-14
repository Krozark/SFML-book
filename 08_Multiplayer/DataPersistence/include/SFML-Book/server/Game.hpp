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

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

namespace book
{
    class Client;
}

class Game : private sfutils::Application<Entity>, public orm::SqlObject<Game>
{
    public:
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        Game();
        Game(const std::string& mapFileName);
        ~Game();

        int getTeamCount();
        int getPlayersCount();

        int id()const;

        bool addClient(book::Client* client);

        void run();
        void stop();
        void wait();

        Entity& createEntity(const sf::Vector2i& coord,std::shared_ptr<Team> team,book::MakeAs makeAs);
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

        using FuncType = std::function<void(book::Client*)>;
        FuncType onLogOut;

        MAKE_STATIC_COLUMN(_id,_mapFileName)

        void load(bool init);

    private:
        friend class EntityData;

        bool _isRunning;
        sf::Thread _gameThread;
        sf::Mutex _gameMutex;
        sfutils::VMap* _map;

        std::list<std::uint32_t> _destroyEntityId;
        std::set<std::uint32_t> _updateEntitiesId;
        std::set<std::uint32_t> _updateTeamId;
        std::list<book::packet::OnHittedEntity::Data> _onHitted;
        std::list<book::packet::OnHitEntity::Data> _onHit;
        std::set<std::uint32_t> _onSpawn;

        book::packet::CreateEntity _createEntities;

        sf::Vector2i _minCoord;
        sf::Vector2i _maxCoord;

        sf::Mutex _teamMutex;
        std::vector<std::shared_ptr<Team>> _teams;

        sf::Mutex _clientsMutex;
        std::vector<book::Client*> _clients;

        void _send();
        sf::Thread _sendThread;
        sf::Mutex _sendMutex;
        std::queue<sf::Packet> _outgoing;


        orm::IntegerField _id;
        static int _numberOfCreations;

        void _run();

        orm::CharField<255> _mapFileName;

        void processNetworkEvents();
        void sendUpdates();

        void update(sf::Time deltaTime);

        void sendToAll(sf::Packet& packet);

        std::unordered_map<sf::Vector2i,std::list<Entity*>> _byCoords;

        // Helpers
        void addUpdate(book::packet::UpdateEntity& packet,unsigned int id);
        void addCreate(book::packet::CreateEntity& packet,unsigned int id);

        virtual void after_load() override;
        virtual void after_save() override;
        virtual void after_update() override;
};
#endif
