#ifndef BOOK_PACKET_P_HPP
#define BOOK_PACKET_P_HPP

#include <SFML-Book/common/FuncIds.hpp>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

namespace book
{
    namespace packet
    {
        class position
        {
            public:
                position(std::uint32_t entityId,const sf::Vector2f& pos);
                position();

                sf::Packet& operator>>(sf::Packet&);
                sf::Packet& operator<<(sf::Packet&);

            private:
                sf::Uint32 _entityId;
                sf::Vector2f& _pos;
        };
    }
}
#endif
