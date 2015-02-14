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
                case FuncIds::IdDisconnected :
                {
                    res = new Disconnected();
                    packet>>(*static_cast<Disconnected*>(res));
                }break;
                case FuncIds::IdGetListGame :
                {
                    res = new GetListGame();
                    packet>>(*static_cast<GetListGame*>(res));
                }break;
                case FuncIds::IdSetListGame :
                {
                    res = new SetListGame();
                    packet>>(*static_cast<SetListGame*>(res));
                }break;
                case FuncIds::IdCreateGame :
                {
                    res = new CreateGame();
                    packet>>(*static_cast<CreateGame*>(res));
                }break;
                case FuncIds::IdJoinGame :
                {
                    res = new JoinGame();
                    packet>>(*static_cast<JoinGame*>(res));
                }break;
                case FuncIds::IdJoinGameConfirmation :
                {
                    res = new JoinGameConfirmation();
                    packet>>(*static_cast<JoinGameConfirmation*>(res));
                }break;
                case FuncIds::IdJoinGameReject :
                {
                    res = new JoinGameReject();
                    packet>>(*static_cast<JoinGameReject*>(res));
                }break;
                case FuncIds::IdRequestCreateEntity :
                {
                    //TODO
                }break;
                case FuncIds::IdRequestDestroyEntity :
                {
                    //TODO
                }break;
                case FuncIds::IdDestroyEntity :
                {
                    //TODO
                }break;
                case FuncIds::IdCreateEntity :
                {
                    //TODO
                }break;
                case FuncIds::IdUpdateEntity:
                {
                    res = new UpdateEntity();
                    packet>>(*static_cast<UpdateEntity*>(res));
                }break;
                case FuncIds::IdHittedEntity :
                {
                    //TODO
                }break;
                case FuncIds::IdHitEntity :
                {
                    //TODO
                }break;
                case FuncIds::IdAddGoldTeam :
                {
                    //TODO
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

        void SetListGame::add(int id,int players,int teams)
        {
            Game tmp = {.nbTeams = teams,
                .nbPlayers = players,
                .id = id};

            _list.emplace_back(std::move(tmp));
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

        ////////////////// Create game /////////////////
        CreateGame::CreateGame() : NetworkEvent(FuncIds::IdCreateGame)
        {
        }

        //////////////// Join Game ////////////////
    
        JoinGame::JoinGame() : NetworkEvent(FuncIds::IdJoinGame), _gameId(-1)
        {
        }

        JoinGame::JoinGame(int gameId) : NetworkEvent(FuncIds::IdJoinGame), _gameId(gameId)
        {
        }

        int JoinGame::gameId()const
        {
            return _gameId;
        }

        sf::Packet& operator<<(sf::Packet& packet, const JoinGame& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Int32(self._gameId);
            return packet;
        }

        sf::Packet& operator>>(sf::Packet& packet, JoinGame& self)
        {
            sf::Int32 id;
            packet>>id;
            self._gameId = id;
            return packet;
        }

        /////////////////////// JoinGameConfirmation //////////////////////////

        JoinGameConfirmation::JoinGameConfirmation() : NetworkEvent(FuncIds::IdJoinGameConfirmation)
        {
        }

        JoinGameConfirmation::JoinGameConfirmation(const std::string& mapDatas,const sf::Color& color) : NetworkEvent(FuncIds::IdJoinGameConfirmation), _mapDatas(mapDatas), _teamColor(color)
        {
        }

        const std::string& JoinGameConfirmation::getMapDatas()const
        {
            return _mapDatas;
        }

        const sf::Color& JoinGameConfirmation::getTeamColor()const
        {
            return _teamColor;
        }

        sf::Packet& operator>>(sf::Packet& packet, JoinGameConfirmation& self)
        {
            sf::Int8 r,g,b;

            self._mapDatas.clear();
            packet>>self._mapDatas
                >>r
                >>g
                >>b;
            self._teamColor = sf::Color(r,g,b);

            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const JoinGameConfirmation& self)
        {
            packet<<sf::Uint8(self._type)
                <<self._mapDatas
                <<sf::Int8(self._teamColor.r)
                <<sf::Int8(self._teamColor.g)
                <<sf::Int8(self._teamColor.g);

            return packet;
        }

        ////////////////////// JoinGameReject ///////////////////////

        JoinGameReject::JoinGameReject() : NetworkEvent(FuncIds::IdJoinGameReject), _gameId(-1)
        {
        }

        JoinGameReject::JoinGameReject(int id) : NetworkEvent(FuncIds::IdJoinGameReject), _gameId(id)
        {
        }

        sf::Packet& operator>>(sf::Packet& packet, JoinGameReject& self)
        {
            sf::Int32 id;
            packet>>id;
            self._gameId = id;
            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const JoinGameReject& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Int32(self._gameId);
            return packet;
        }

        //////////////////////////// UpdateEntity /////////////////////

        UpdateEntity::UpdateEntity() : NetworkEvent(FuncIds::IdUpdateEntity)
        {
        }

        void UpdateEntity::add(UpdateEntity::Update&& update)
        {
            _updates.emplace_back(update);
        }

        const std::list<UpdateEntity::Update>& UpdateEntity::getUpdates()const
        {
            return _updates;
        }

        sf::Packet& operator>>(sf::Packet& packet, UpdateEntity& self)
        {
            sf::Uint32 size;
            packet>>size;
            self._updates.clear();
            for(unsigned int i=0;i<size;++i)
            {
                UpdateEntity::Update update;
                sf::Uint32 entityId;
                sf::Int8 entityType;
                sf::Int8 animationId;
                sf::Int32 coord_x;
                sf::Int32 coord_y;
                sf::Int32 hp;

                packet>>entityId
                    >>entityType
                    >>animationId
                    >>update.position.x
                    >>update.position.y
                    >>coord_x
                    >>coord_y
                    >>hp;

                update.entityId = entityId;
                update.entityType = entityType;
                update.animationId = animationId;
                update.coord.x = coord_x;
                update.coord.y = coord_y;

                update.hp = hp;

                self._updates.emplace_back(std::move(update));

            }
            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const UpdateEntity& self)
        {
            packet<<sf::Uint32(self._updates.size());
            for(const UpdateEntity::Update& update : self._updates)
            {
                packet<<sf::Uint32(update.entityId)
                    <<sf::Int8(update.entityType)
                    <<sf::Int8(update.animationId)
                    <<update.position.x
                    <<update.position.y
                    <<sf::Int32(update.coord.x)
                    <<sf::Int32(update.coord.y)
                    <<sf::Int32(update.hp);
            }
            return packet;
        }

    }
}
