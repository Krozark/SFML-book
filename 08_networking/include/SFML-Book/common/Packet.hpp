#ifndef BOOK_PACKET_PACKET_HPP
#define BOOK_PACKET_PACKET_HPP

#include <SFML-Book/common/FuncIds.hpp>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

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

            protected:
                const FuncIds::FUNCIDS _type;

        };

        class GetListGame : public NetworkEvent
        {
            public:
                GetListGame();

                friend sf::Packet& operator>>(sf::Packet&, GetListGame& self);
                friend sf::Packet& operator<<(sf::Packet&, const GetListGame& self);
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
