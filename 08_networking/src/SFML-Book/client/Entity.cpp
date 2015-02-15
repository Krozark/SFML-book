#include <SFML-Book/client/Entity.hpp>
#include <SFML-Book/client/Component.hpp>
#include <SFML-Book/client/Team.hpp>
#include <SFML-Book/client/Level.hpp>

#include <SFML-Book/common/FuncIds.hpp>
#include <SFML-Book/common/Configuration.hpp>

ES_INIT_ENTITY(book::Entity);

namespace book
{
    Entity::Entity(sfutils::EntityManager<Entity>* manager,std::uint32_t id) : sfutils::Entity<Entity>(manager,id), onHit(nullptr), onHitted(nullptr)
    {
        name = "???";
    }

    sf::Vector2f Entity::getPosition()const
    {
        return component<CompSkin>()->_sprite.getPosition();
    }

    void Entity::setPosition(const sf::Vector2f& pos)
    {
        component<CompSkin>()->_sprite.setPosition(pos);
    }

    void Entity::draw(sf::RenderTarget& target,sf::RenderStates states)const
    {
        target.draw(component<CompSkin>()->_sprite,states);

        CompHp::Handle hp = component<CompHp>();
        if(hp.isValid())
        {
            hp->update(getPosition());
            hp->draw(target,states);
        }
    }

    ////////// UTILTS /////////////

    void setAnimation(Entity& entity,int animationId,int animationMap,float ox,float oy,float sx,float sy)
    {
        CompSkin& skin = *entity.component<CompSkin>().get();
        sfutils::Animation& animation = Configuration::animations.get(animationId);

        skin._animations.emplace(animationMap,&animation);
        skin._sprite.setAnimation(skin._animations.at(animationMap));

        //resize to map size
        sf::IntRect rec = animation.getRect(0);
        skin._sprite.setOrigin(rec.width*ox,rec.height*oy);
        skin._sprite.setScale(sx,sy);
    }

    void setTeam(Entity& entity,Team* team)
    {
        if(team)
        {
            entity.add<CompTeam>(team);
            entity.component<CompSkin>()->_sprite.setColor(team->getColor());
        }
    }


    //////////////////// Helpers ///////////////////////
    void makeAs(unsigned int entityType,Entity& e,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
        switch(entityType)
        {
            case EntityType::IdMain :
            {
                makeAsMain(e,team,level,data);
            }break;
            case EntityType::IdEye : 
            {
                makeAsEye(e,team,level,data);
            }break;
            case EntityType::IdWormEgg :
            {
                makeAsWormEgg(e,team,level,data);
            }break;
            case EntityType::IdWorm :
            {
                makeAsWorm(e,team,level,data);
            }break;
            case EntityType::IdCarnivor :
            {
                makeAsCarnivor(e,team,level,data);
            }break;
            default : break;
        }
    }


    void makeAsMain(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
        setAnimation(entity,Configuration::AnimMainStand,CompSkin::Spawn,0.5,0.7,0.25,0.25);
        setAnimation(entity,Configuration::AnimMainStand,CompSkin::Stand,0.5,0.7,0.25,0.25);

        //add team
        setTeam(entity,team);

        entity.add<CompAISpawner>([](Level& lvl,const sf::Vector2i& pos){
                                    //TODO makeAsVoltageEffect(lvl.createEntity(pos));
                                  });
        entity.add<CompHp>(data.hp);
        entity.add<CompBuildArea>(4);

        entity.onHitted = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHittedMain,myCoord);
            //TODO makeAsVoltageEffect(lvl.createEntity(myCoord));
        };

        entity.name = "QG";

    }

    void makeAsEye(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
    }

    void makeAsWormEgg(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
    }

    void makeAsWorm(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
    }

    void makeAsCarnivor(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
    }
}
