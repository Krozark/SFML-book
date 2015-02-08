#include <SFML-Book/common/Packet.hpp>

namespace book
{
    namespace packet
    {
        sf::Packet& position::operator<<(sf::Packet& packet)
        {
            packet<<sf::Uint8(FuncIds::setPosition)
                <<_entityId
                <<_pos.x
                <<_pos.y;
            return packet;
        }

        sf::Packet& position::operator>>(sf::Packet& packet)
        {
            packet>>_entityId
                >>_pos.x
                >>_pos.y;
            return packet;
        }
    }
}
