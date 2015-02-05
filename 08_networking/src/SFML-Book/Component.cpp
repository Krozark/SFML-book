#include <SFML-Book/Component.hpp>

namespace book
{
    CompAIMain::CompAIMain(int gold,const sf::Time& timeDelta) :_gold_amount(gold),_delta(timeDelta), _elapsed(sf::Time::Zero)
    {
    }

    CompAIWarrior::CompAIWarrior(int hitPoint,const sf::Time& timeDelta,int range) : _hitPoint(hitPoint), _delta(timeDelta), _elapsed(sf::Time::Zero), _range(range)
    {
    }

    CompAIDefender::CompAIDefender(int hitPoint,const sf::Time& timeDelta,int range) : _hitPoint(hitPoint), _delta(timeDelta), _elapsed(sf::Time::Zero), _range(range)
    {
    }

    CompAISpawner::CompAISpawner(CompAISpawner::FuncType makeAs,int number,const sf::Time& timeDelta, CompAISpawner::FuncType_onSpawn onSpawn) : _makeAs(makeAs), _number(number), _delta(timeDelta), _elapsed(sf::Time::Zero), _OnSpawn(onSpawn)
    {
    }

    CompAIWalker::CompAIWalker(float speed) : _speed(speed)
    {
    }

    CompAIFlyer::CompAIFlyer(float speed) : _speed(speed)
    {
    }

    CompTeam::CompTeam(Team* team) : _team(team)
    {
    }


    const float CompHp::_height = 5;
    const float CompHp::_width = 0.05;

    CompHp::CompHp(int hp) : _hp(hp), _maxHp(hp)
    {
        float width = _width*_hp;

        _shape_max_hp.setFillColor(sf::Color::Red);
        _shape_max_hp.setOutlineThickness(1);
        _shape_max_hp.setOutlineColor(sf::Color::Black);

        _shape_max_hp.setSize(sf::Vector2f(width,_height));
        _shape_max_hp.setOrigin(width/2,_height/2);

        _shape_hp.setFillColor(sf::Color::Green);
        _shape_hp.setOutlineThickness(1);
        _shape_hp.setOutlineColor(sf::Color::Black);

        _shape_hp.setSize(sf::Vector2f(width,_height));
        _shape_hp.setOrigin(width/2,_height/2);

    }

    void CompHp::update(const sf::Vector2f& pos)
    {
        float width = _width*_hp;
        _shape_hp.setSize(sf::Vector2f(width,_height));
        _shape_hp.setPosition(pos.x,pos.y-50);

        _shape_max_hp.setPosition(pos.x,pos.y-50);
    }

    void CompHp::draw(sf::RenderTarget& target,sf::RenderStates states)
    {
        target.draw(_shape_max_hp,states);
        target.draw(_shape_hp,states);
    }

    CompBuildArea::CompBuildArea(int range) : _range(range)
    {
    }
}
