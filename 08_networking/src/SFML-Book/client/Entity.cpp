#include <SFML-Book/client/Entity.hpp>
#include <SFML-Book/client/Component.hpp>
#include <SFML-Book/client/Team.hpp>
#include <SFML-Book/client/Level.hpp>

#include <SFML-Book/common/FuncIds.hpp>
#include <SFML-Book/common/Configuration.hpp>
#include <SFML-Book/common/random.hpp>

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
            default :
            {
                std::cout<<"ERROR Unknow Entity Created"<<std::endl;
            }break;
        }

        e.type = entityType;
    }

    ////////////////////////// helpers  //////////////////////////////

    void makeAsMain(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
        setAnimation(entity,Configuration::AnimMainStand,CompSkin::Spawn,0.5,0.7,0.25,0.25);
        setAnimation(entity,Configuration::AnimMainStand,CompSkin::Stand,0.5,0.7,0.25,0.25);

        //add team
        setTeam(entity,team);

        entity.add<CompAISpawner>([](Level& lvl,const sf::Vector2i& pos){
                                    lvl.addEffect(makeVoltageEffect,pos);
                                  });
        entity.add<CompHp>(data.hp,data.maxHp);
        entity.add<CompBuildArea>(4);

        entity.onHitted = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHittedMain,myCoord);
            lvl.addEffect(makeVoltageEffect,myCoord);
        };

        entity.name = "QG";

    }

    void makeAsEye(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
        setAnimation(entity,Configuration::AnimEyeLeft,CompSkin::MoveLeft,0.5,0.8,0.5,0.5);
        setAnimation(entity,Configuration::AnimEyeRight,CompSkin::MoveRight,0.5,0.8,0.5,0.5);

        sf::Vector2f pos = entity.component<CompSkin>()->_sprite.getPosition();
        level.createSound(Configuration::SoundSpawnEye,pos);

        //add team
        setTeam(entity,team);

        entity.add<CompHp>(data.hp,data.maxHp);

        entity.onHitted = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHittedEye,myCoord);
            lvl.addEffect(makeBloodEffect,myCoord);
        };

        entity.onHit = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHitEye,myCoord);
        };

        entity.name = "Fleye";

    }

    void makeAsWormEgg(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
        setAnimation(entity,Configuration::AnimWormEggBirth,CompSkin::Spawn,0.5,0.9,0.3,0.3);
        setAnimation(entity,Configuration::AnimWormEggStand,CompSkin::Stand,0.5,0.9,0.3,0.3);

        setTeam(entity,team);
        entity.add<CompAISpawner>([](Level& lvl,const sf::Vector2i& pos){
                                    lvl.addEffect(makeFlashEffect,pos);
                                  });
        entity.add<CompHp>(data.hp,data.maxHp);
        entity.add<CompBuildArea>(2);

        entity.name = "Worm Egg";
    }

    void makeAsWorm(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
        setAnimation(entity,Configuration::AnimWormLeft,CompSkin::MoveLeft,0.5,0.8,0.4,0.4);
        setAnimation(entity,Configuration::AnimWormRight,CompSkin::MoveRight,0.5,0.8,0.4,0.4);

        sf::Vector2f pos = entity.component<CompSkin>()->_sprite.getPosition();
        level.createSound(Configuration::SoundSpawnWormEgg,pos);

        setTeam(entity,team);

        entity.add<CompHp>(data.hp,data.maxHp);

        entity.onHitted = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHittedWorm,myCoord);
            lvl.addEffect(makeBloodEffect,myCoord);
        };

        entity.onHit = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHitWorm,myCoord);
        };

        entity.name = "Worm";
    }

    void makeAsCarnivor(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data)
    {
        setAnimation(entity,Configuration::AnimCarnivorStand,CompSkin::Stand,0.5,0.9,0.4,0.4);

        setTeam(entity,team);

        entity.add<CompHp>(data.hp,data.maxHp);
        entity.add<CompBuildArea>(2);

        entity.onHitted = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHittedWorm,myCoord);
            lvl.addEffect(makeBloodEffect,myCoord);
        };

        entity.onHit = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHitWorm,myCoord);
        };

        entity.name = "Carnivor";
    }

    //////////////////// Effects ///////////////////////////

    Effect::Effect(int animationId)
    {
        sfutils::Animation& animation = Configuration::animations.get(animationId);
        sprite.setAnimation(&animation);
        sprite.setLoop(false);
        
        sf::IntRect rec = animation.getRect(0);
        sprite.setOrigin(rec.width*0.5,rec.height*0.5);
    }

    sf::Vector2f Effect::getPosition()const
    {
        return sprite.getPosition();
    }

    void Effect::setPosition(const sf::Vector2f& pos)
    {
        sprite.setPosition(pos);
    }

    void Effect::draw(sf::RenderTarget& target,sf::RenderStates states) const
    {
        target.draw(sprite,states);
    }

    Effect* makeBloodEffect()
    {
        int animation = random(Configuration::AnimBlood1,Configuration::AnimBlood4);
        return new Effect(animation);
    }
    Effect* makeFlashEffect()
    {
        return new Effect(Configuration::AnimFlash);
    }

    Effect* makeVoltageEffect()
    {
        return new Effect(Configuration::AnimVoltage);
    }    
}
