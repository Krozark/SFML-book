#ifndef BOOK_HELPERS_HPP
#define BOOK_HELPERS_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Map.hpp>

#include <SFML-Book/common/Entity.hpp>
#include <SFML-Book/common/Configuration.hpp>

namespace book
{
    class Team;
    class Level;

    //////////// EFFECTS ////////////////
    void makeAsEffect(Entity& entity,int animation);
    void makeAsBloodEffect(Entity& entity);
    void makeAsFlashEffect(Entity& entity);
    void makeAsVoltageEffect(Entity& entity);


}
#endif
