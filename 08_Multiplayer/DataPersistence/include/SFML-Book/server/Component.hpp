#ifndef BOOK_COMPONENT_HPP
#define BOOK_COMPONENT_HPP

#include <unordered_map>

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Core.hpp>

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-Book/server/Entity.hpp>

namespace book
{
    class Team;
    class Game;
}

    class CompAIMain : public sfutils::Component<CompAIMain,book::Entity>, public orm::SqlObject<CompAIMain>
    {
        public:
            CompAIMain();
            explicit CompAIMain(int gold,const sf::Time& timeDelta);

            virtual void after_load() override;
            virtual void before_save() override;
            virtual void before_update() override;

            orm::IntegerField _gold_amount;

            sf::Time _delta;
            orm::DoubleField _deltaAsDOuble;

            sf::Time _elapsed;
            orm::DoubleField _elapsedAsDouble;

            MAKE_STATIC_COLUMN(_gold_amount,_deltaAsDOuble,_elapsedAsDouble)
    };
    

    struct CompAIWarrior : sfutils::Component<CompAIWarrior,book::Entity>
    {
        explicit CompAIWarrior(int hitPoint,const sf::Time& timeDelta,int range);

        const int _hitPoint;
        const sf::Time _delta;
        sf::Time _elapsed;
        const int _range;
        std::uint32_t _enemyId;
    };

    struct CompAIDefender : sfutils::Component<CompAIDefender,book::Entity>
    {
        explicit CompAIDefender(int hitPoint,const sf::Time& timeDelta,int range);

        const int _hitPoint;
        const sf::Time _delta;
        sf::Time _elapsed;
        const int _range;
    };

    struct CompAISpawner : sfutils::Component<CompAISpawner,book::Entity>
    {
        using FuncType = std::function<void(book::Entity& entity,book::Team* team,book::Game& game)>;

        explicit CompAISpawner(FuncType makeAs,int number,const sf::Time& timeDelta);
        
        FuncType _makeAs;
        const int _number;
        const sf::Time _delta;
        sf::Time _elapsed;
    };

    struct CompAIWalker : sfutils::Component<CompAIWalker,book::Entity>
    {
        explicit CompAIWalker(float speed);

        const float _speed;
        sf::Vector2i _pathToTake;
    };

    struct CompAIFlyer : sfutils::Component<CompAIFlyer,book::Entity>
    {
        explicit CompAIFlyer(float speed);

        const float _speed;
        sf::Vector2i _pathToTake;
    };

    struct CompTeam : sfutils::Component<CompTeam,book::Entity>
    {
        explicit CompTeam(book::Team* team);
        book::Team* _team;
    };

    struct CompSkin : sfutils::Component<CompSkin,book::Entity>
    {
        enum AnimationId : int{
            Stand = 0,
            Spawn,
            MoveLeft,
            MoveRight,
            HitLeft,
            HitRight
        };

        explicit CompSkin(short int animation);
        
        short int _animationId;
    };

    struct CompHp : sfutils::Component<CompHp,book::Entity>
    {
        explicit CompHp(int hp);

        int _hp;
        const int _maxHp;
    };


#endif
