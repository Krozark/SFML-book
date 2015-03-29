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
        orm::DoubleField _deltaAsDouble;

        sf::Time _elapsed;
        orm::DoubleField _elapsedAsDouble;

        MAKE_STATIC_COLUMN(_gold_amount,_deltaAsDouble,_elapsedAsDouble)
};


class CompAIWarrior : public sfutils::Component<CompAIWarrior,book::Entity>, public orm::SqlObject<CompAIWarrior>
{
    public:
        CompAIWarrior();
        explicit CompAIWarrior(int hitPoint,const sf::Time& timeDelta,int range);
    
        virtual void after_load() override;
        virtual void before_save() override;
        virtual void before_update() override;

        orm::IntegerField _hitPoint;

        sf::Time _delta;
        orm::DoubleField _deltaAsDouble;

        sf::Time _elapsed;
        orm::DoubleField _elapsedAsDouble;

        orm::IntegerField _range;
        orm::UnsignedIntegerField _enemyId;

        MAKE_STATIC_COLUMN(_hitPoint,_deltaAsDouble,_elapsedAsDouble,_range,_enemyId)
};

class CompAIDefender : public sfutils::Component<CompAIDefender,book::Entity>, public orm::SqlObject<CompAIDefender>
{
    public:
        CompAIDefender();
        explicit CompAIDefender(int hitPoint,const sf::Time& timeDelta,int range);

        virtual void after_load() override;
        virtual void before_save() override;
        virtual void before_update() override;

        orm::IntegerField _hitPoint;

        sf::Time _delta;
        orm::DoubleField _deltaAsDouble;

        sf::Time _elapsed;
        orm::DoubleField _elapsedAsDouble;

        orm::IntegerField _range;

        MAKE_STATIC_COLUMN(_hitPoint,_deltaAsDouble,_elapsedAsDouble,_range)
};

class CompAISpawner : public sfutils::Component<CompAISpawner,book::Entity>, public orm::SqlObject<CompAISpawner>
{
    public:
        using FuncType = std::function<void(book::Entity& entity,book::Team* team,book::Game& game)>;

        CompAISpawner();
        explicit CompAISpawner(FuncType makeAs,int number,const sf::Time& timeDelta);

        virtual void after_load() override;
        virtual void before_save() override;
        virtual void before_update() override;
    
        FuncType _makeAs;
        orm::IntegerField _makeAsTypeId;

        orm::IntegerField _number;

        sf::Time _delta;
        orm::DoubleField _deltaAsDouble;

        sf::Time _elapsed;
        orm::DoubleField _elapsedAsDouble;

        MAKE_STATIC_COLUMN(_makeAsTypeId,_number,_deltaAsDouble,_elapsedAsDouble)
};

class CompAIWalker : public sfutils::Component<CompAIWalker,book::Entity>, public orm::SqlObject<CompAIWalker>
{
    public:
        CompAIWalker();
        explicit CompAIWalker(float speed);

        virtual void after_load() override;
        virtual void before_save() override;
        virtual void before_update() override;

        orm::FloatField _speed;

        sf::Vector2i _pathToTake;
        orm::IntegerField _pathToTakeX;
        orm::IntegerField _pathToTakeY;

        MAKE_STATIC_COLUMN(_speed,_pathToTakeX,_pathToTakeY)
};

class CompAIFlyer : public sfutils::Component<CompAIFlyer,book::Entity>, public orm::SqlObject<CompAIFlyer>
{
    public:
        CompAIFlyer();
        explicit CompAIFlyer(float speed);

        virtual void after_load() override;
        virtual void before_save() override;
        virtual void before_update() override;

        orm::FloatField _speed;

        sf::Vector2i _pathToTake;
        orm::IntegerField _pathToTakeX;
        orm::IntegerField _pathToTakeY;

        MAKE_STATIC_COLUMN(_speed,_pathToTakeX,_pathToTakeY)
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
