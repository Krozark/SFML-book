#ifndef BOOK_SYSTEM_HPP
#define BOOK_SYSTEM_HPP

#include <SFML-utils/ES.hpp>

#include <SFML-Book/Entity.hpp>

namespace book
{
    class Level;
    
    struct SysAIMain : sfutils::System<SysAIMain,Entity>
    {
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
    };

    struct SysAIWarrior : sfutils::System<SysAIWarrior,Entity>
    {
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
    };

    struct SysAIDefender : sfutils::System<SysAIDefender,Entity>
    {
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
    };

    struct SysAISpawner : sfutils::System<SysAISpawner,Entity>
    {
        explicit SysAISpawner(Level& level);
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;

        Level& _level;
    };

    struct SysAIWalker : sfutils::System<SysAISpawner,Entity>
    {
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
    };

    struct SysAIFlyer : sfutils::System<SysAIFlyer,Entity>
    {
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
    };

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
