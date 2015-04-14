#ifndef BOOK_HELPERS_HPP
#define BOOK_HELPERS_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Map.hpp>

#include <SFML-Book/Entity.hpp>
#include <SFML-Book/Configuration.hpp>

namespace book
{
    class Team;
    class Level;

    void makeAsMain(Entity& entity,Team* team,Level& level);
    void makeAsEye(Entity& entity,Team* team,Level& level);
    void makeAsWormEgg(Entity& entity,Team* team, Level& level);
    void makeAsWorm(Entity& entity,Team* team, Level& level);
    void makeAsCarnivor(Entity& entity,Team* team, Level& level);
    
    //////////// EFFECTS ////////////////
    void makeAsEffect(Entity& entity,int animation);
    void makeAsBloodEffect(Entity& entity);
    void makeAsFlashEffect(Entity& entity);
    void makeAsVoltageEffect(Entity& entity);

    ////////// UTILTS /////////////
    void setTeam(Entity& entity,Team* team);
    void setAnimation(Entity& entity,int animationId,int animationMap,float ox=0,float oy=0,float sx=1,float sy=1);

    enum BuildEntities {
        EntityMain,
        EntityWormEgg,
        EntityCarnivor,
        SIZE
    };


    struct Info {
        int cost;
        std::string name;
        std::function<void(Entity&,Team*,Level&)> makeAs;
        int icon_id;
        int animation_id;
        std::string description;
    };

    static Info informations[SIZE] = {
        {5000, "GQ",makeAsMain, Configuration::TexBuildMain, Configuration::AnimMainStand,"Main building.\nGenerates gold.\nYou loose the game\nif you don't control\nany one of them."},
        {250, "Worm Egg",makeAsWormEgg,Configuration::TexBuildWormEgg, Configuration::AnimWormEggStand, "Spawn some worms"},
        {300, "Carnivor",makeAsCarnivor, Configuration::TexBuildCarnivor, Configuration::AnimCarnivorStand, "Make hight damage"}
    };

}
#endif
