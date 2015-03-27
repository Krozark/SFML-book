#ifndef BOOK_SYSTEM_HPP
#define BOOK_SYSTEM_HPP

#include <SFML-utils/ES.hpp>

#include <SFML-Book/client/Entity.hpp>

namespace book
{
    class Level;
    
    struct SysSkin : sfutils::System<SysSkin,Entity>
    {
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
    };

    struct SysHp : sfutils::System<SysHp,Entity>
    {
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
    };
}
#endif
