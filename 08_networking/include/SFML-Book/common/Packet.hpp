#ifndef BOOK_PACKET_PACKET_HPP
#define BOOK_PACKET_PACKET_HPP

#include <SFML-Book/common/FuncIds.hpp>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <list>

namespace book
{
    namespace packet
    {
        // base
        class NetworkEvent
        {
            public:
                NetworkEvent(FuncIds::FUNCIDS type);
                virtual ~NetworkEvent();

                FuncIds::FUNCIDS type()const;

                static NetworkEvent* makeFromPacket(sf::Packet& packet);

                friend sf::Packet& operator>>(sf::Packet&, NetworkEvent& self);
                friend sf::Packet& operator<<(sf::Packet&, const NetworkEvent& self);

            protected:
                const FuncIds::FUNCIDS _type;

        };

        //specials

        class Disconnected : public NetworkEvent
        {
            public:
                Disconnected();
        };

        // main menu
        class GetListGame : public NetworkEvent
        {
            public:
                GetListGame();
        };

        class SetListGame : public NetworkEvent
        {
            public:
                SetListGame();

                friend sf::Packet& operator>>(sf::Packet&, SetListGame& self);
                friend sf::Packet& operator<<(sf::Packet&, const SetListGame& self);

                void add(int id,int players,int teams);
                
                struct Game {
                    int nbTeams;
                    int nbPlayers;
                    int id;
                };

                const std::list<SetListGame::Game>& list()const;
                
            private:
                std::list<SetListGame::Game> _list;
        };

        class CreateGame : public NetworkEvent
        {
            public :
                CreateGame();
        };

        class JoinGame : public NetworkEvent
        {
            public:
                JoinGame();
                JoinGame(int gameId);

                int gameId()const;

                friend sf::Packet& operator>>(sf::Packet&, JoinGame& self);
                friend sf::Packet& operator<<(sf::Packet&, const JoinGame& self);

            private:
                int _gameId;
        };

        class JoinGameConfirmation : public NetworkEvent
        {
            public:
                JoinGameConfirmation();
                JoinGameConfirmation(const std::string& mapDatas,int team);

                const std::string& getMapDatas()const;
                int getTeamId()const;

                friend sf::Packet& operator>>(sf::Packet&, JoinGameConfirmation& self);
                friend sf::Packet& operator<<(sf::Packet&, const JoinGameConfirmation& self);

                struct Data{
                    int team;
                    int gold;
                    sf::Color color;
                };

                const void addTeam(Data&& data);
                const std::list<Data>& getTeamInfo()const;

            private:
                std::string _mapDatas;
                int _teamId;
                std::list<Data> _teamInfo;
        };

        class JoinGameReject : public NetworkEvent
        {
            public:
                JoinGameReject();
                JoinGameReject(int id);

                int gameId()const;

                friend sf::Packet& operator>>(sf::Packet&, JoinGameReject& self);
                friend sf::Packet& operator<<(sf::Packet&, const JoinGameReject& self);
            private:
                int _gameId;
        };

        //in game
        
        //RequestCreateEntity, //client
        //RequestDestroyEntity, //client
        //DestroyEntity, //server
        //CreateEntity, //server
        class CreateEntity : public NetworkEvent
        {
            public :
                CreateEntity();

                struct Data {
                    unsigned int entityId;
                    short int entityType;
                    short int entityTeam;
                    short int animationId;
                    sf::Vector2f position;
                    sf::Vector2i coord;
                    int hp;
                };

                void add(Data&& update);
                const std::list<Data>& getCreates()const;
                void clear();

                friend sf::Packet& operator>>(sf::Packet&, CreateEntity& self);
                friend sf::Packet& operator<<(sf::Packet&, const CreateEntity& self);


            private :
                std::list<Data> _updates;
        };

        class UpdateEntity : public NetworkEvent
        {
            public :
                UpdateEntity();

                struct Data {
                    unsigned int entityId;
                    short int animationId;
                    sf::Vector2f position;
                    sf::Vector2i coord;
                    int hp;
                };

                void add(Data&& update);
                const std::list<Data>& getUpdates()const;
                void clear();

                friend sf::Packet& operator>>(sf::Packet&, UpdateEntity& self);
                friend sf::Packet& operator<<(sf::Packet&, const UpdateEntity& self);

            private :
                std::list<Data> _updates;
        };

        //IdHittedEntity, //server
        //IdHitEntity, //server
        class UpdateTeam : public NetworkEvent
        {
            public :
                UpdateTeam();

                struct Data {
                    short int team;
                    bool gameOver;
                    int gold;
                };

                void add(Data&& update);
                const std::list<Data>& getUpdates()const;

                friend sf::Packet& operator>>(sf::Packet&, UpdateTeam& self);
                friend sf::Packet& operator<<(sf::Packet&, const UpdateTeam& self);

            private:
                std::list<Data> _updates;

        };

    }
}
#endif
