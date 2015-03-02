#ifndef BOOK_SYSTEM_HPP
#define BOOK_SYSTEM_HPP

#include <SFML-utils/ES.hpp>

#include <SFML-Book/server/Entity.hpp>

namespace book
{
    class Game;
    
    struct SysAIMain : sfutils::System<SysAIMain,Entity>
    {
        explicit SysAIMain(Game& game);
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
        Game& _game;
    };

    struct SysAIWarrior : sfutils::System<SysAIWarrior,Entity>
    {
        explicit SysAIWarrior(Game& game);
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
        Game& _game;
    };

    struct SysAIDefender : sfutils::System<SysAIDefender,Entity>
    {
        explicit SysAIDefender(Game& game);
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
        Game& _game;
    };

    struct SysAISpawner : sfutils::System<SysAISpawner,Entity>
    {
        explicit SysAISpawner(Game& game);
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;

        Game& _game;
    };

    struct SysAIWalker : sfutils::System<SysAIWalker,Entity>
    {
        explicit SysAIWalker(Game& game);
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
        Game& _game;
    };

    struct SysAIFlyer : sfutils::System<SysAIFlyer,Entity>
    {
        explicit SysAIFlyer(Game& game);
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
        Game& _game;
    };

    struct SysHp : sfutils::System<SysHp,Entity>
    {
        explicit SysHp(Game& game);
        virtual void update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt) override;
        Game& _game;
    };

}
#endif
