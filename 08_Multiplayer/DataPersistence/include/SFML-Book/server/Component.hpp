#ifndef BOOK_COMPONENT_HPP
#define BOOK_COMPONENT_HPP

#include <unordered_map>

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Core.hpp>

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-Book/server/Entity.hpp>
#include <SFML-Book/server/Team.hpp>

class Game;

class CompAIMain : public sfutils::Component<CompAIMain,Entity>, public orm::SqlObject<CompAIMain>
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


class CompAIWarrior : public sfutils::Component<CompAIWarrior,Entity>, public orm::SqlObject<CompAIWarrior>
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

class CompAIDefender : public sfutils::Component<CompAIDefender,Entity>, public orm::SqlObject<CompAIDefender>
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

class CompAISpawner : public sfutils::Component<CompAISpawner,Entity>, public orm::SqlObject<CompAISpawner>
{
    public:

        CompAISpawner();
        explicit CompAISpawner(book::MakeAs makeAs,int number,const sf::Time& timeDelta);

        virtual void after_load() override;
        virtual void before_save() override;
        virtual void before_update() override;
    
        book::MakeAs _makeAs;
        orm::IntegerField _makeAsTypeId;

        orm::IntegerField _number;

        sf::Time _delta;
        orm::DoubleField _deltaAsDouble;

        sf::Time _elapsed;
        orm::DoubleField _elapsedAsDouble;

        MAKE_STATIC_COLUMN(_makeAsTypeId,_number,_deltaAsDouble,_elapsedAsDouble)
};

class CompAIWalker : public sfutils::Component<CompAIWalker,Entity>, public orm::SqlObject<CompAIWalker>
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

class CompAIFlyer : public sfutils::Component<CompAIFlyer,Entity>, public orm::SqlObject<CompAIFlyer>
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

class CompTeam : public sfutils::Component<CompTeam,Entity>, public orm::SqlObject<CompTeam>
{
    public:
        CompTeam();
        explicit CompTeam(Team::type_ptr team);

        //book::Team* _team;

        orm::FK<Team> _team;
        
        MAKE_STATIC_COLUMN(_team)
};

struct CompSkin : sfutils::Component<CompSkin,Entity>
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

struct CompHp : sfutils::Component<CompHp,Entity>
{
    explicit CompHp(int hp);

    int _hp;
    const int _maxHp;
};


#endif
