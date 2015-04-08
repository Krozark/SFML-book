#ifndef BOOK_ENTITYDATA_HPP
#define BOOK_ENTITYDATA_HPP

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-Book/server/Component.hpp>
#include <SFML-Book/server/Game.hpp>

class Entity;

class EntityData : public orm::SqlObject<EntityData>
{
    public:
        EntityData();

        static EntityData::type_ptr createFromEntity(Entity& entity,Game::type_ptr game);
        
        std::uint32_t convertToEntity(Game& game);

        orm::FK<Game> _game;
        orm::FloatField _coordX;
        orm::FloatField _coordY;
        orm::IntegerField _type;

        orm::FK<CompAIMain> _AIMain;
        orm::FK<CompAIWarrior> _AIWarrior;
        orm::FK<CompAIDefender> _AIDefender;
        orm::FK<CompAISpawner> _AISpawner;
        orm::FK<CompAIWalker> _AIWalker;
        orm::FK<CompAIFlyer> _AIFlyer;
        orm::FK<CompTeam> _team;
        orm::FK<CompSkin> _skin;
        orm::FK<CompHp> _hp;

        virtual void after_load() override;
        virtual void before_save() override;
        virtual void before_update() override;

        MAKE_STATIC_COLUMN(_game,_coordX,_coordY,_type,\
                           _AIMain,_AIWarrior,_AIDefender,\
                           _AISpawner,_AIWalker,_AIFlyer,\
                           _team,_skin,_hp)

};

#endif
