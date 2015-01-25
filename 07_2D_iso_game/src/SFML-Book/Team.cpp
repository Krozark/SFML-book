
#include <SFML-Book/Team.hpp>

namespace book
{
    Team::Team(sf::RenderWindow& window,int id,const sf::Color& color) : isAlive(true),gui(window,color),_id(id), _points(0), _gold(0), _QGId(0)
    {
    }

    void Team::addGold(int amount)
    {
        if(amount > 0)
        {
            _gold += amount;
            gui.setGold(_gold);
        }
    }

    void Team::addEnemy(Team* team)
    {
        _enemies.emplace_back(team);
    }

    const std::list<Team*>& Team::getEnemies()const
    {
        return _enemies;
    }

    void Team::setQgId(std::uint32_t id)
    {
        _QGId = id;
    }

    std::uint32_t Team::getQgId()
    {
        return _QGId;
    }

    int Team::id()const
    {
        return _id;
    }
}
