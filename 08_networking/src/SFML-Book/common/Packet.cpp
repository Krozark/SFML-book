#include <SFML-Book/common/Packet.hpp>

#include <SFML-Book/server/Game.hpp>

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
                case FuncIds::IdDisconnected :
                {
                    res = new Disconnected;
                    packet>>(*static_cast<Disconnected*>(res));
                }break;
                case FuncIds::IdGetListGame :
                {
                    res = new GetListGame;
                    packet>>(*static_cast<GetListGame*>(res));
                }break;
                case FuncIds::IdSetListGame :
                {
                    res = new SetListGame;
                    packet>>(*static_cast<SetListGame*>(res));
                }break;
                case FuncIds::IdSelectGame :
                {
                }break;
                case FuncIds::IdPosition :
                {
                    res = new Position;
                    packet>>(*static_cast<Position*>(res));
                }break;
            }
            return res;
        }
        FuncIds::FUNCIDS NetworkEvent::type()const
        {
            return _type;
        }

        sf::Packet& operator>>(sf::Packet& packet, NetworkEvent& self)
        {
            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const NetworkEvent& self)
        {
            packet<<sf::Uint8(self._type);
            return packet;
        }

        ////////////////////// Disconnected ////////////////////
        
        Disconnected::Disconnected() : NetworkEvent(FuncIds::IdDisconnected)
        {
        }


        ////////////////// Get List Game //////////////////////

        GetListGame::GetListGame() : NetworkEvent(FuncIds::IdGetListGame)
        {
        }

        /////////////////////////////// Set List Game ////////////////////

        SetListGame::SetListGame() : NetworkEvent(FuncIds::IdSetListGame)
        {
        }

        SetListGame::SetListGame(const std::list<book::Game*>& list) : SetListGame()
        {
            for(book::Game* game : list)
            {
                Game tmp = {.nbTeams = game->getTeamCount(),
                    .nbPlayers = game->getPalyersCount(),
                    .id = game->id()};

                _list.emplace_back(std::move(tmp));
            }
        }

        sf::Packet& operator>>(sf::Packet& packet, SetListGame& self)
        {
            sf::Uint32 size;
            packet>>size;
            self._list.clear();
            for(unsigned int i=0;i<size;++i)
            {
                sf::Int32 id;
                sf::Int32 teams;
                sf::Int32 players;

                packet>>id
                    >>teams
                    >>players;

                SetListGame::Game game = {.nbTeams = teams,
                    .nbPlayers = players,
                    .id = id};

                self._list.emplace_back(std::move(game));

            }
            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const SetListGame& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Uint32(self._list.size());

            for(const SetListGame::Game& game : self._list)
            {
                packet<<sf::Int32(game.id)
                    <<sf::Int32(game.nbTeams)
                    <<sf::Int32(game.nbPlayers);
            }
            return packet;
        }

        const std::list<SetListGame::Game>& SetListGame::list()const
        {
            return _list;
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
