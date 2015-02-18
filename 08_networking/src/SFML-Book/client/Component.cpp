#include <SFML-Book/client/Component.hpp>

namespace book
{
    CompAISpawner::CompAISpawner(CompAISpawner::FuncType_onSpawn onSpawn) : _onSpawn(onSpawn)
    {
    }

    CompTeam::CompTeam(Team* team) : _team(team)
    {
    }


    const float CompHp::_height = 5;
    const float CompHp::_width = 0.05;

    CompHp::CompHp(int hp,int maxHp) : _hp(hp), _maxHp(maxHp)
    {
        float width = _width*_maxHp;

        _shapeMaxHp.setFillColor(sf::Color::Red);
        _shapeMaxHp.setOutlineThickness(1);
        _shapeMaxHp.setOutlineColor(sf::Color::Black);

        _shapeMaxHp.setSize(sf::Vector2f(width,_height));
        _shapeMaxHp.setOrigin(width/2,_height/2);

        _shapeHp.setFillColor(sf::Color::Green);
        _shapeHp.setOutlineThickness(1);
        _shapeHp.setOutlineColor(sf::Color::Black);

        _shapeHp.setSize(sf::Vector2f(width,_height));
        _shapeHp.setOrigin(width/2,_height/2);

    }

    void CompHp::update(const sf::Vector2f& pos)
    {
        float width = _width*_hp;
        _shapeHp.setSize(sf::Vector2f(width,_height));
        _shapeHp.setPosition(pos.x,pos.y-50);

        _shapeMaxHp.setPosition(pos.x,pos.y-50);
    }

    void CompHp::draw(sf::RenderTarget& target,sf::RenderStates states)
    {
        target.draw(_shapeMaxHp,states);
        target.draw(_shapeHp,states);
    }

    CompBuildArea::CompBuildArea(int range) : _range(range)
    {
    }
}
