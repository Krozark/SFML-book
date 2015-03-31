#include <SFML-Book/server/EntityData.hpp>
#include <SFML-Book/server/Entity.hpp>


REGISTER_AND_CONSTRUCT(EntityData,"EntityData",\
         _game,"game_id",\
         _coordX,"coordX",\
         _coordY,"coordY",\
         _type,"type",\
         _AIMain,"AIMain",\
         _AIWarrior,"AIWarrior",\
         _AIDefender,"AIDefender",\
         _AISpawner,"AISpawner",\
         _AIWalker,"AIWalker",\
         _AIFlyer,"AIFlyer",\
         _team,"team",\
         _skin,"skin",\
         _hp,"hp")

EntityData::type_ptr EntityData::createFromEntity(Entity& entity)
{
    sf::Vector2i coords = entity.getCoord();


    EntityData::type_ptr e = EntityData::create();

    //e->_game = game;
    e->_coordX = coords.x;
    e->_coordY = coords.y;
    e->_type = entity.getType();

    if(entity.has<CompAIMain>())
    {
        CompAIMain* comp_raw_ptr = entity.component<CompAIMain>().get();
        comp_raw_ptr->save();
        //CompAIMain::type_ptr comp_ptr = CompAIMain::get(comp_raw_ptr->getPk());//as_type_ptr();

        //e->_AIMain = comp_ptr;
    }

    return e;
}

void EntityData::after_load()
{

    sf::Vector2i coords(_coordX,_coordY);

    book::MakeAs makAs = book::getMakeAs(_type);
}

void EntityData::before_save()
{

}

void EntityData::before_update()
{
    before_save();
}
