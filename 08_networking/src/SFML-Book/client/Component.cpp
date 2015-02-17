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
