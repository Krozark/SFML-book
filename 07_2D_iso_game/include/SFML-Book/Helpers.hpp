#ifndef BOOK_HELPERS_HPP
#define BOOK_HELPERS_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Map.hpp>

#include <SFML-Book/Entity.hpp>

namespace book
{
    class Team;

    void makeAsMain(Entity& entity,Team* team);

    void setTeam(Entity& entity,Team* team);
    void setAnimation(Entity& entity,int animationId,int animationMap,float ox=0,float oy=0,float sx=1,float sy=1);

}
#endif
