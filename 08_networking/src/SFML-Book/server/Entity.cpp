#include <SFML-Book/server/Entity.hpp>

#include <SFML-Book/common/FuncIds.hpp>
#include <SFML-Book/server/Component.hpp>
#include <SFML-Book/server/Team.hpp>

ES_INIT_ENTITY(book::Entity);

namespace book
{
    Entity::Entity(sfutils::EntityManager<Entity>* manager,std::uint32_t id) : sfutils::Entity<Entity>(manager,id)
    {
    }

    sf::Vector2f Entity::getPosition()const
    {
        return _position;
    }

    sf::Vector2i Entity::getCoord()const
    {
        return _coords;
    }

    void Entity::setType(short int type)
    {
        _type = type;
    }

    short int Entity::getType()const
    {
        return _type;
    }

    void Entity::setPosition(const sf::Vector2f& pos, const sf::Vector2i& coord)
    {
        _position = pos;
        _coords = coord;
    }


    /************* Helpers *****************/

    MakeAs getMakeAs(int id)
    {
        switch(id)
        {
            case EntityType::IdMain :
                return makeAsMain;
            case EntityType::IdEye :
                return makeAsEye;
            case EntityType::IdWormEgg :
                return makeAsWormEgg;
            case EntityType::IdWorm :
                return makeAsWorm;
            case EntityType::IdCarnivor :
                return makeAsCarnivor;
            default : return nullptr;
        }
    }

    void makeAsMain(Entity& entity,Team* team,Game& game)
    {
        entity.setType(EntityType::IdMain);
        entity.add<CompTeam>(team);
        entity.add<CompSkin>(CompSkin::Stand);
        
        team->addQgId(entity.id());

        //add AI
        entity.add<CompAIMain>(100,sf::seconds(10));
        entity.add<CompAISpawner>(makeAsEye,1,sf::seconds(5));
        entity.add<CompHp>(5000);

    }

    void makeAsEye(Entity& entity,Team* team,Game& game)
    {
        entity.setType(EntityType::IdEye);
        entity.add<CompTeam>(team);
        entity.add<CompSkin>(CompSkin::MoveRight);

        entity.add<CompAIWarrior>(50,sf::seconds(0.7),1);
        entity.add<CompHp>(500);
        entity.add<CompAIFlyer>(200);

    }

    void makeAsWormEgg(Entity& entity,Team* team,Game& game)
    {
        entity.setType(EntityType::IdWormEgg);
        entity.add<CompTeam>(team);
        entity.add<CompSkin>(CompSkin::Stand);
        
        entity.add<CompAISpawner>(makeAsWorm,1,sf::seconds(15));
        entity.add<CompHp>(200);

    }

    void makeAsWorm(Entity& entity,Team* team,Game& game)
    {
        entity.setType(EntityType::IdWorm);
        entity.add<CompTeam>(team);
        entity.add<CompSkin>(CompSkin::MoveRight);

        entity.add<CompAIWarrior>(20,sf::seconds(0.5),1);
        entity.add<CompHp>(250);
        entity.add<CompAIWalker>(70);

    }

    void makeAsCarnivor(Entity& entity,Team* team,Game& game)
    {
        entity.setType(EntityType::IdCarnivor);
        entity.add<CompTeam>(team);
        entity.add<CompSkin>(CompSkin::Stand);

        entity.add<CompAIWarrior>(120,sf::seconds(0.9),1);
        entity.add<CompHp>(500);
    }

}
