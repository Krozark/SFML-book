#include <SFML-Book/common/Packet.hpp>

namespace book
{
    namespace packet
    {
        NetworkEvent::NetworkEvent(FuncIds::FUNCIDS type) : _type(type)
        {
        }

        NetworkEvent::~NetworkEvent()
        {
        }

        NetworkEvent* NetworkEvent::makeFromPacket(sf::Packet& packet)
        {
            sf::Uint8 id;
            NetworkEvent* res = nullptr;
            packet>>id;
            switch(id)
            {
                case FuncIds::IdGetListGame :
                {
                    res = new GetListGame;
                    packet>>(*static_cast<GetListGame*>(res));
                }break;
                case FuncIds::IdSelectGame :
                {
                }break;
                case FuncIds::IdPosition :
                {
                    res = new Position;
                    packet>>(*static_cast<Position*>(res));
                }break;
                default : break;
            }
            return res;
        }
        FuncIds::FUNCIDS NetworkEvent::type()const
        {
            return _type;
        }

        ////////////////// Get List Game //////////////////////

        GetListGame::GetListGame() : NetworkEvent(FuncIds::IdGetListGame)
        {
        }

        sf::Packet& operator>>(sf::Packet& packet, GetListGame& self)
        {
            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const GetListGame& self)
        {
            packet<<sf::Uint8(self._type);
            return packet;
        }

        ///////////////////// Position //////////////////////////

        Position::Position(): NetworkEvent(FuncIds::IdPosition)
        {}

        Position::Position(std::uint32_t entityId,const sf::Vector2f& pos) : Position()
        {}

        sf::Packet& operator>>(sf::Packet& packet, Position& self)
        {
            packet>>self._entityId
                >>self._pos.x
                >>self._pos.y;
            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet,const Position& self)
        {
            packet<<sf::Uint8(self._type)
                <<self._entityId
                <<self._pos.x
                <<self._pos.y;
            return packet;
        }

        std::uint32_t Position::getId()const
        {
            return _entityId;
        }

        const sf::Vector2f& Position::getPosition()const
        {
            return _pos;
        }
    }
}
