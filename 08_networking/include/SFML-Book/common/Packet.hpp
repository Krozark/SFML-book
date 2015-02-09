#ifndef BOOK_PACKET_PACKET_HPP
#define BOOK_PACKET_PACKET_HPP

#include <SFML-Book/common/FuncIds.hpp>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <list>

namespace book
{
    class Game;
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
                SetListGame(const std::list<book::Game*>& list);

                friend sf::Packet& operator>>(sf::Packet&, SetListGame& self);
                friend sf::Packet& operator<<(sf::Packet&, const SetListGame& self);
                
                struct Game {
                    int nbTeams;
                    int nbPlayers;
                    int id;
                };

                const std::list<SetListGame::Game>& list()const;
                
            private:
                std::list<SetListGame::Game> _list;
        };


        class Position : public NetworkEvent
        {
            public:
                Position(std::uint32_t entityId,const sf::Vector2f& pos);
                Position();

                friend sf::Packet& operator>>(sf::Packet&, Position& self);
                friend sf::Packet& operator<<(sf::Packet&, const Position& self);

                std::uint32_t getId()const;
                const sf::Vector2f& getPosition()const;

            private:
                sf::Uint32 _entityId;
                sf::Vector2f _pos;
        };
    }
}
#endif
