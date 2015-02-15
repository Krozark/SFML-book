#include <SFML-Book/common/Helpers.hpp>
#include <SFML-Book/common/Component.hpp>
#include <SFML-Book/common/Team.hpp>
#include <SFML-Book/common/random.hpp>
#include <SFML-Book/common/Level.hpp>

namespace book
{
    
    void makeAsMain(Entity& entity,Team* team,Level& level)
    {
        //add animation
        setAnimation(entity,Configuration::AnimMainStand,CompSkin::Spawn,0.5,0.7,0.25,0.25);
        setAnimation(entity,Configuration::AnimMainStand,CompSkin::Stand,0.5,0.7,0.25,0.25);

        //add team
        setTeam(entity,team);
        team->addQgId(entity.id());

        //add AI
        entity.add<CompAIMain>(100,sf::seconds(10));
        entity.add<CompAISpawner>(makeAsEye,1,sf::seconds(5),
                                  [](Level& lvl,const sf::Vector2i& pos){
                                    makeAsVoltageEffect(lvl.createEntity(pos));
                                  });
        entity.add<CompHp>(5000);
        entity.add<CompBuildArea>(4);

        entity.onHitted = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHittedMain,myCoord);
            makeAsVoltageEffect(lvl.createEntity(myCoord));
        };

        entity.name = "QG";
    }

    void makeAsEye(Entity& entity,Team* team,Level& level)
    {
        //add animation
        setAnimation(entity,Configuration::AnimEyeLeft,CompSkin::MoveLeft,0.5,0.8,0.5,0.5);
        setAnimation(entity,Configuration::AnimEyeRight,CompSkin::MoveRight,0.5,0.8,0.5,0.5);

        sf::Vector2f pos = entity.component<CompSkin>()->_sprite.getPosition();
        level.createSound(Configuration::SoundSpawnEye,pos);

        //add team
        setTeam(entity,team);

        //add AI
        entity.add<CompAIWarrior>(50,sf::seconds(0.7),1);
        entity.add<CompHp>(500);
        entity.add<CompAIFlyer>(200);
        //entity.component<CompAIFlyer>->_pathToTake = 

        entity.onHitted = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHittedEye,myCoord);
            makeAsBloodEffect(lvl.createEntity(myCoord));
        };

        entity.onHit = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHitEye,myCoord);
        };

        entity.name = "Fleye";
    }

    void makeAsWormEgg(Entity& entity,Team* team,Level& level)
    {
        setAnimation(entity,Configuration::AnimWormEggBirth,CompSkin::Spawn,0.5,0.9,0.3,0.3);
        setAnimation(entity,Configuration::AnimWormEggStand,CompSkin::Stand,0.5,0.9,0.3,0.3);

        setTeam(entity,team);
        entity.add<CompAISpawner>(makeAsWorm,1,sf::seconds(15),
                                  [](Level& lvl,const sf::Vector2i& pos){
                                    makeAsFlashEffect(lvl.createEntity(pos));
                                  });
        entity.add<CompHp>(200);
        entity.add<CompBuildArea>(2);

        entity.name = "Worm Egg";
    }

    void makeAsWorm(Entity& entity,Team* team, Level& level)
    {
        setAnimation(entity,Configuration::AnimWormLeft,CompSkin::MoveLeft,0.5,0.8,0.4,0.4);
        setAnimation(entity,Configuration::AnimWormRight,CompSkin::MoveRight,0.5,0.8,0.4,0.4);

        sf::Vector2f pos = entity.component<CompSkin>()->_sprite.getPosition();
        level.createSound(Configuration::SoundSpawnWormEgg,pos);

        setTeam(entity,team);

        entity.add<CompAIWarrior>(20,sf::seconds(0.5),1);
        entity.add<CompHp>(250);
        entity.add<CompAIWalker>(70);

        entity.onHitted = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHittedWorm,myCoord);
            makeAsBloodEffect(lvl.createEntity(myCoord));
        };

        entity.onHit = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            lvl.createSound(Configuration::SoundHitWorm,myCoord);
        };

        entity.name = "Worm";
    }

    void makeAsCarnivor(Entity& entity,Team* team, Level& level)
    {
        setAnimation(entity,Configuration::AnimCarnivorStand,CompSkin::Stand,0.5,0.9,0.4,0.4);

        setTeam(entity,team);

        entity.add<CompAIWarrior>(120,sf::seconds(0.9),1);
        entity.add<CompHp>(500);
        entity.add<CompBuildArea>(2);

        entity.onHitted = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            //lvl.createSound(Configuration::SoundHittedWorm,myCoord);
            makeAsBloodEffect(lvl.createEntity(myCoord));
        };

        entity.onHit = [](Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& lvl){
            //lvl.createSound(Configuration::SoundHitWorm,myCoord);
        };

        entity.name = "Carnivor";
    }

    //////////// EFFECTS ////////////////
    void makeAsEffect(Entity& entity,int animation)
    {
        setAnimation(entity,animation,CompSkin::Stand,0.5,0.5);

        CompSkin& skin = *entity.component<CompSkin>().get();
        skin._sprite.setRepeate(1);
        skin._sprite.setLoop(false);
        skin._sprite.move(0,1);

        entity.add<CompEffect>();
    }

    void makeAsBloodEffect(Entity& entity)
    {
        int animation = random(Configuration::AnimBlood1,Configuration::AnimBlood4);
        makeAsEffect(entity,animation);
        entity.name = "Blood";
    }

    void makeAsFlashEffect(Entity& entity)
    {
        makeAsEffect(entity,Configuration::AnimFlash);

        entity.name = "Flash";
    }

    void makeAsVoltageEffect(Entity& entity)
    {
        makeAsEffect(entity,Configuration::AnimVoltage);

        entity.name = "Voltage";
    }
}
