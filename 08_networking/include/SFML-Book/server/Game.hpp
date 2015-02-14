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

#include <SFML-Book/server/std_hash.hpp>
#include <SFML-Book/server/Entity.hpp>

#include <SFML-Book/common/Packet.hpp>

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

            void destroyEntity(std::uint32_t id);
            void setPosition(Entity& e,const sf::Vector2i& oldCoord,const sf::Vector2f& pos,const sf::Vector2i& newCoord);


            std::list<sf::Vector2i> getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const;
            sf::Vector2i getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const;
            int getDistance(const sf::Vector2i& origin,const sf::Vector2i& dest)const;


        private:
            bool _isRunning;
            sf::Thread _gameThread;
            sf::Mutex _gameMutex;
            sfutils::VMap* _map;

            std::set<std::uint32_t> _updateEntitiesId;
            
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
            void update(sf::Time deltaTime);

            void sendToAll(sf::Packet& packet);

            std::unordered_map<sf::Vector2i,std::list<Entity*>> _byCoords;

            // Helpers
            void addUpdate(packet::UpdateEntity& packet,unsigned int id);
            void addCreate(packet::CreateEntity& packet,unsigned int id);
    };
}
#endif
