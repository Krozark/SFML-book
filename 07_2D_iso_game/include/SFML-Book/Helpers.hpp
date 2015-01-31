#ifndef BOOK_HELPERS_HPP
#define BOOK_HELPERS_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Map.hpp>

#include <SFML-Book/Entity.hpp>

namespace book
{
    class Team;
    class Level;

    void makeAsMain(Entity& entity,Team* team,Level& level);
    void makeAsEye(Entity& entity,Team* team,Level& level);
    void makeAsWormEgg(Entity& entity,Team* team, Level& level);
    void makeAsWorm(Entity& entity,Team* team, Level& level);
    
    //////////// EFFECTS ////////////////
    void makeAsEffect(Entity& entity,int animation);
    void makeAsBloodEffect(Entity& entity);
    void makeAsFlashEffect(Entity& entity);
    void makeAsVoltageEffect(Entity& entity);

    ////////// UTILTS /////////////
    void setTeam(Entity& entity,Team* team);
    void setAnimation(Entity& entity,int animationId,int animationMap,float ox=0,float oy=0,float sx=1,float sy=1);

    enum Entities {
        EntityMain,
        EntityWormEgg,
        SIZE
    };

    static int Cost[SIZE] = {
        5000,
        200
    };

}
#endif
