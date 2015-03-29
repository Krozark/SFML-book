#include <SFML-Book/server/Component.hpp>


/////////// CompAIMain ///////////////

    REGISTER_AND_CONSTRUCT(CompAIMain,"CompAIMain",\
                           _gold_amount,"gold_amount",\
                           _deltaAsDOuble,"deltaAsDOuble",\
                           _elapsedAsDouble,"elapsedAsDouble")


    CompAIMain::CompAIMain(int gold,const sf::Time& timeDelta) :CompAIMain()
    {
        _gold_amount = gold;
        _delta = timeDelta;
        _elapsed = sf::Time::Zero;
    }

    void CompAIMain::after_load()
    {
        _delta = sf::seconds(_deltaAsDOuble);
        _elapsed = sf::seconds(_elapsedAsDouble);
    }

    void CompAIMain::before_save()
    {
        _deltaAsDOuble = _delta.asSeconds();
        _elapsedAsDouble = _elapsed.asSeconds();
    }

    void CompAIMain::before_update()
    {
        before_save(); 
    }   

    CompAIWarrior::CompAIWarrior(int hitPoint,const sf::Time& timeDelta,int range) : _hitPoint(hitPoint), _delta(timeDelta), _elapsed(sf::Time::Zero), _range(range), _enemyId(-1)
    {
    }

    CompAIDefender::CompAIDefender(int hitPoint,const sf::Time& timeDelta,int range) : _hitPoint(hitPoint), _delta(timeDelta), _elapsed(sf::Time::Zero), _range(range)
    {
    }

    CompAISpawner::CompAISpawner(CompAISpawner::FuncType makeAs,int number,const sf::Time& timeDelta) : _makeAs(makeAs), _number(number), _delta(timeDelta), _elapsed(sf::Time::Zero)
    {
    }

    CompAIWalker::CompAIWalker(float speed) : _speed(speed)
    {
    }

    CompAIFlyer::CompAIFlyer(float speed) : _speed(speed)
    {
    }

    CompTeam::CompTeam(book::Team* team) : _team(team)
    {
    }

    CompSkin::CompSkin(short int animation) : _animationId(animation)
    {
    }

    CompHp::CompHp(int hp) : _hp(hp), _maxHp(hp)
    {
    }

