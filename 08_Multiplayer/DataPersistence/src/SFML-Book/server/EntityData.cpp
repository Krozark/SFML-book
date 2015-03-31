#include <SFML-Book/server/EntityData.hpp>


REGISTER_AND_CONSTRUCT(EntityData,"EntityData",\
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
