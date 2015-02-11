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

        class Disconnected : public NetworkEvent
        {
            public:
                Disconnected();
        };

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
                JoinGameConfirmation(const std::string& mapDatas);

                const std::string& getMapDatas()const;

                friend sf::Packet& operator>>(sf::Packet&, JoinGameConfirmation& self);
                friend sf::Packet& operator<<(sf::Packet&, const JoinGameConfirmation& self);

            private:
                std::string _mapDatas;
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


        class MoveEntity : public NetworkEvent
        {
            public:
                MoveEntity(std::uint32_t entityId,const sf::Vector2f& pos);
                MoveEntity();

                friend sf::Packet& operator>>(sf::Packet&, MoveEntity& self);
                friend sf::Packet& operator<<(sf::Packet&, const MoveEntity& self);

                std::uint32_t getId()const;
                const sf::Vector2f& getPosition()const;

            private:
                sf::Uint32 _entityId;
                sf::Vector2f _pos;
        };
    }
}
#endif
