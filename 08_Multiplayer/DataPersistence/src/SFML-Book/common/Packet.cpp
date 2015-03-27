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
                case FuncIds::IdLogOut :
                {
                    res = new LogOut();
                    packet>>(*static_cast<LogOut*>(res));
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
                    res = new RequestCreateEntity();
                    packet>>(*static_cast<RequestCreateEntity*>(res));
                }break;
                case FuncIds::IdRequestDestroyEntity :
                {
                    res = new RequestDestroyEntity();
                    packet>>(*static_cast<RequestDestroyEntity*>(res));
                }break;
                case FuncIds::IdDestroyEntity :
                {
                    res = new DestroyEntity();
                    packet>>(*static_cast<DestroyEntity*>(res));
                }break;
                case FuncIds::IdCreateEntity :
                {
                    res = new CreateEntity();
                    packet>>(*static_cast<CreateEntity*>(res));

                }break;
                case FuncIds::IdUpdateEntity:
                {
                    res = new UpdateEntity();
                    packet>>(*static_cast<UpdateEntity*>(res));
                }break;
                case FuncIds::IdOnHittedEntity :
                {
                    res = new OnHittedEntity();
                    packet>>(*static_cast<OnHittedEntity*>(res));
                }break;
                case FuncIds::IdOnHitEntity :
                {
                    res = new OnHitEntity();
                    packet>>(*static_cast<OnHitEntity*>(res));
                }break;
                case FuncIds::IdOnSpawnEntity :
                {
                    res = new OnSpawnEntity();
                    packet>>(*static_cast<OnSpawnEntity*>(res));
                }break;
                case FuncIds::IdUpdateTeam :
                {
                    res = new UpdateTeam();
                    packet>>(*static_cast<UpdateTeam*>(res));
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

        //////////////////// LogOut /////////////////////////////////

        LogOut::LogOut() : NetworkEvent(FuncIds::IdLogOut)
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

        JoinGameConfirmation::JoinGameConfirmation(const std::string& mapDatas,int team): NetworkEvent(FuncIds::IdJoinGameConfirmation), _mapDatas(mapDatas), _teamId(team)
        {
        }

        const std::string& JoinGameConfirmation::getMapDatas()const
        {
            return _mapDatas;
        }

        int JoinGameConfirmation::getTeamId()const
        {
            return _teamId;
        }

        const void JoinGameConfirmation::addTeam(JoinGameConfirmation::Data&& data)
        {
            _teamInfo.emplace_back(data);
        }

        const std::list<JoinGameConfirmation::Data>& JoinGameConfirmation::getTeamInfo()const
        {
            return _teamInfo;
        }

        sf::Packet& operator>>(sf::Packet& packet, JoinGameConfirmation& self)
        {
            self._mapDatas.clear();

            sf::Int32 teamId;
            sf::Int32 nbTeam;

            packet>>self._mapDatas
                >>teamId
                >>nbTeam;
            self._teamId = teamId;

            self._teamInfo.clear();
            for(int i=0;i<nbTeam;++i)
            {
                sf::Int32 team;
                sf::Int32 gold;
                sf::Uint8 r,g,b;

                packet>>team
                    >>gold
                    >>r>>g>>b;
                JoinGameConfirmation::Data data;
                data.team = team;
                data.gold = gold;
                data.color = sf::Color(r,g,b);

                self._teamInfo.emplace_back(std::move(data));
            }

            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const JoinGameConfirmation& self)
        {
            packet<<sf::Uint8(self._type)
                <<self._mapDatas
                <<sf::Int32(self._teamId)
                <<sf::Int32(self._teamInfo.size());
            for(const JoinGameConfirmation::Data& data: self._teamInfo)
            {
                packet<<sf::Int32(data.team)
                    <<sf::Int32(data.gold)
                    <<sf::Uint8(data.color.r)
                    <<sf::Uint8(data.color.g)
                    <<sf::Uint8(data.color.b);
            }

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

        //////////////////// RequestCreateEntity /////////////////////

        RequestCreateEntity::RequestCreateEntity() : NetworkEvent(FuncIds::IdRequestCreateEntity)
        {
        }

        RequestCreateEntity::RequestCreateEntity(short int type,const sf::Vector2i& coord) : NetworkEvent(FuncIds::IdRequestCreateEntity), _entitytype(type), _coord(coord)
        {
        }

        short int RequestCreateEntity::getType()const
        {
            return _entitytype;
        }

        const sf::Vector2i& RequestCreateEntity::getCoord()const
        {
            return _coord;
        }

        sf::Packet& operator>>(sf::Packet& packet, RequestCreateEntity& self)
        {
            sf::Int8 type;
            sf::Int32 x,y;

            packet>>type
                >>x
                >>y;

            self._entitytype = type;
            self._coord.x = x;
            self._coord.y = y;

            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const RequestCreateEntity& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Int8(self._entitytype)
                <<sf::Int32(self._coord.x)
                <<sf::Int32(self._coord.y);
            return packet;
        }


        ///////////////////////// RequestDestroyEntity ///////////////////

        RequestDestroyEntity::RequestDestroyEntity() : NetworkEvent(FuncIds::IdRequestDestroyEntity)
        {
        }

        RequestDestroyEntity::RequestDestroyEntity(unsigned int id) : NetworkEvent(FuncIds::IdRequestDestroyEntity), _id(id)
        {
        }

        unsigned int RequestDestroyEntity::getId()const
        {
            return _id;
        }

        sf::Packet& operator>>(sf::Packet& packet, RequestDestroyEntity& self)
        {
            sf::Uint32 id;
            packet>>id;
            self._id = id;
            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const RequestDestroyEntity& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Uint32(self._id);
            return packet;
        }
        
        
        //////////////////////////// DestroyEntity /////////////////////

        DestroyEntity::DestroyEntity() : NetworkEvent(FuncIds::IdDestroyEntity)
        {
        }

        void DestroyEntity::add(unsigned int id)
        {
            _updates.emplace_back(id);
        }

        const std::list<unsigned int>& DestroyEntity::getDestroy()const
        {
            return _updates;
        }

        sf::Packet& operator>>(sf::Packet& packet, DestroyEntity& self)
        {
            sf::Uint32 size;
            packet>>size;
            self._updates.clear();
            for(unsigned int i=0;i<size;++i)
            {
                sf::Uint32 entityId;
                packet>>entityId;
                self._updates.emplace_back(entityId);
            }
            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const DestroyEntity& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Uint32(self._updates.size());
            for(unsigned int id : self._updates)
            {
                packet<<sf::Uint32(id);
            }
            return packet;
        }

        //////////////////////////// CreateEntity /////////////////////

        CreateEntity::CreateEntity() : NetworkEvent(FuncIds::IdCreateEntity)
        {
        }

        void CreateEntity::add(CreateEntity::Data&& update)
        {
            _updates.emplace_back(update);
        }

        const std::list<CreateEntity::Data>& CreateEntity::getCreates()const
        {
            return _updates;
        }

        void CreateEntity::clear()
        {
            _updates.clear();
        }

        sf::Packet& operator>>(sf::Packet& packet, CreateEntity& self)
        {
            sf::Uint32 size;
            packet>>size;
            self._updates.clear();
            for(unsigned int i=0;i<size;++i)
            {
                CreateEntity::Data update;
                sf::Uint32 entityId;
                sf::Int8 entityType;
                sf::Int8 entityTeam;
                sf::Int8 animationId;
                sf::Int32 coord_x;
                sf::Int32 coord_y;
                sf::Int32 maxHp;
                sf::Int32 hp;

                packet>>entityId
                    >>entityType
                    >>entityTeam
                    >>animationId
                    >>update.position.x
                    >>update.position.y
                    >>coord_x
                    >>coord_y
                    >>maxHp
                    >>hp;

                update.entityId = entityId;
                update.entityType = entityType;
                update.entityTeam = entityTeam;
                update.animationId = animationId;
                update.coord.x = coord_x;
                update.coord.y = coord_y;
                update.maxHp = maxHp;
                update.hp = hp;

                self._updates.emplace_back(std::move(update));

            }
            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const CreateEntity& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Uint32(self._updates.size());
            for(const CreateEntity::Data& update : self._updates)
            {
                packet<<sf::Uint32(update.entityId)
                    <<sf::Int8(update.entityType)
                    <<sf::Int8(update.entityTeam)
                    <<sf::Int8(update.animationId)
                    <<update.position.x
                    <<update.position.y
                    <<sf::Int32(update.coord.x)
                    <<sf::Int32(update.coord.y)
                    <<sf::Int32(update.maxHp)
                    <<sf::Int32(update.hp);
            }
            return packet;
        }

        //////////////////////////// UpdateEntity /////////////////////

        UpdateEntity::UpdateEntity() : NetworkEvent(FuncIds::IdUpdateEntity)
        {
        }

        void UpdateEntity::add(UpdateEntity::Data&& update)
        {
            _updates.emplace_back(update);
        }

        const std::list<UpdateEntity::Data>& UpdateEntity::getUpdates()const
        {
            return _updates;
        }

        void UpdateEntity::clear()
        {
            _updates.clear();
        }

        sf::Packet& operator>>(sf::Packet& packet, UpdateEntity& self)
        {
            sf::Uint32 size;
            packet>>size;
            self._updates.clear();
            for(unsigned int i=0;i<size;++i)
            {
                UpdateEntity::Data update;
                sf::Uint32 entityId;
                sf::Int8 animationId;
                sf::Int32 coord_x;
                sf::Int32 coord_y;
                sf::Int32 hp;

                packet>>entityId
                    >>animationId
                    >>update.position.x
                    >>update.position.y
                    >>coord_x
                    >>coord_y
                    >>hp;

                update.entityId = entityId;
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
            packet<<sf::Uint8(self._type)
                <<sf::Uint32(self._updates.size());
            for(const UpdateEntity::Data& update : self._updates)
            {
                packet<<sf::Uint32(update.entityId)
                    <<sf::Int8(update.animationId)
                    <<update.position.x
                    <<update.position.y
                    <<sf::Int32(update.coord.x)
                    <<sf::Int32(update.coord.y)
                    <<sf::Int32(update.hp);
            }
            return packet;
        }

        ///////////////////////// OnHittedEntity ///////////////////

        OnHittedEntity::OnHittedEntity() : NetworkEvent(FuncIds::IdOnHittedEntity)
        {
        }

        void OnHittedEntity::add(OnHittedEntity::Data&& data)
        {
            _updates.emplace_back(data);
        }

        const std::list<OnHittedEntity::Data>& OnHittedEntity::getHitted()const
        {
            return _updates;
        }

        sf::Packet& operator>>(sf::Packet& packet, OnHittedEntity& self)
        {
            self._updates.clear();
            sf::Uint32 size;
            packet>>size;
            for(unsigned int i=0;i<size;++i)
            {
                sf::Uint32 id;
                sf::Int32 x,y,ex,ey;
                sf::Uint32 enemyId;
                packet>>id
                    >>x
                    >>y
                    >>enemyId
                    >>ex
                    >>ey;

                OnHittedEntity::Data data;

                data.entityId = id;
                data.entityCoord.x = x;
                data.entityCoord.y = y;
                data.enemyId = enemyId;
                data.entityCoord.x = ex;
                data.entityCoord.y = ey;

                self.add(std::move(data));
            }

            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const OnHittedEntity& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Uint32(self._updates.size());
            for(const OnHittedEntity::Data& data : self._updates)
            {
                packet<<sf::Uint32(data.entityId)
                    <<sf::Int32(data.entityCoord.x)
                    <<sf::Int32(data.entityCoord.y)
                    <<sf::Uint32(data.enemyId)
                    <<sf::Int32(data.entityCoord.x)
                    <<sf::Int32(data.entityCoord.y);
            }
            return packet;
        }

        ///////////////////////// OnHitEntity ///////////////////

        OnHitEntity::OnHitEntity() : NetworkEvent(FuncIds::IdOnHitEntity)
        {
        }

        void OnHitEntity::add(OnHitEntity::Data&& data)
        {
            _updates.emplace_back(data);
        }

        const std::list<OnHitEntity::Data>& OnHitEntity::getHit()const
        {
            return _updates;
        }

        sf::Packet& operator>>(sf::Packet& packet, OnHitEntity& self)
        {
            self._updates.clear();
            sf::Uint32 size;
            packet>>size;
            for(unsigned int i=0;i<size;++i)
            {
                sf::Uint32 id;
                sf::Int32 x,y,ex,ey;
                sf::Uint32 enemyId;
                packet>>id
                    >>x
                    >>y
                    >>enemyId
                    >>ex
                    >>ey;

                OnHitEntity::Data data;

                data.entityId = id;
                data.entityCoord.x = x;
                data.entityCoord.y = y;
                data.enemyId = enemyId;
                data.entityCoord.x = ex;
                data.entityCoord.y = ey;

                self.add(std::move(data));
            }

            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const OnHitEntity& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Uint32(self._updates.size());
            for(const OnHitEntity::Data& data : self._updates)
            {
                packet<<sf::Uint32(data.entityId)
                    <<sf::Int32(data.entityCoord.x)
                    <<sf::Int32(data.entityCoord.y)
                    <<sf::Uint32(data.enemyId)
                    <<sf::Int32(data.entityCoord.x)
                    <<sf::Int32(data.entityCoord.y);
            }
            return packet;
        }


        ///////////////////////// OnSpawnEntity ///////////////////

        OnSpawnEntity::OnSpawnEntity() : NetworkEvent(FuncIds::IdOnSpawnEntity)
        {
        }

        void OnSpawnEntity::add(unsigned int id)
        {
            _updates.emplace_back(id);
        }

        const std::list<unsigned int>& OnSpawnEntity::getSpawn()const
        {
            return _updates;
        }

        sf::Packet& operator>>(sf::Packet& packet, OnSpawnEntity& self)
        {
            self._updates.clear();
            sf::Uint32 size;
            packet>>size;
            for(unsigned int i=0;i<size;++i)
            {
                sf::Uint32 id;
                packet>>id;
                self.add(id);
            }

            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const OnSpawnEntity& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Uint32(self._updates.size());
            for(unsigned int id : self._updates)
                packet<<sf::Uint32(id);
            return packet;
        }


        ////////////////////// UpdateTeam ///////////////////////////////
        
        UpdateTeam::UpdateTeam() : NetworkEvent(FuncIds::IdUpdateTeam)
        {
        }

        void UpdateTeam::add(UpdateTeam::Data&& data)
        {
            _updates.emplace_back(data);
        }

        const std::list<UpdateTeam::Data>& UpdateTeam::getUpdates()const
        {
            return _updates;
        }

        sf::Packet& operator>>(sf::Packet& packet, UpdateTeam& self)
        {
            self._updates.clear();
            sf::Int32 size;
            packet>>size;
            for(int i=0;i<size;++i)
            {
                sf::Int32 team;
                sf::Uint8 gameOver;
                sf::Int32 gold;
                packet>>team
                    >>gameOver
                    >>gold;

                UpdateTeam::Data data;
                data.team = team;
                data.gameOver = gameOver;
                data.gold = gold;

                self._updates.emplace_back(std::move(data));
            }

            return packet;
        }

        sf::Packet& operator<<(sf::Packet& packet, const UpdateTeam& self)
        {
            packet<<sf::Uint8(self._type)
                <<sf::Uint32(self._updates.size());
            for(const UpdateTeam::Data& data : self._updates)
            {
                packet<<sf::Uint32(data.team)
                    <<sf::Uint8(data.gameOver)
                    <<sf::Int32(data.gold);
            }
            return packet;
        }
    }
}
