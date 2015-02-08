
#include <SFML-Book/server/Team.hpp>

namespace book
{
    Team::Team(int id) : isAlive(true),_id(id), _points(0), _gold(0), _QGId(0)
    {
    }

    void Team::addGold(int amount)
    {
        _gold += amount;
    }

    void Team::addEnemy(Team* team)
    {
        _enemies.emplace_back(team);
    }

    const std::vector<Team*>& Team::getEnemies()const
    {
        return _enemies;
    }

    void Team::addQgId(std::uint32_t id)
    {
        _QGId.emplace_back(id);
    }

    const std::vector<std::uint32_t>& Team::getQgIds()const
    {
        return _QGId;
    }

    void Team::removeQgId(std::uint32_t id)
    {
        size_t size = _QGId.size();
        size_t i=0;
        while(i<size)
        {
            if(_QGId[i] == id)
            {
                _QGId.erase(_QGId.begin()+i);
                --size;
            }
            else
            ++i;
        }
        isAlive = _QGId.size()>0;
    }

    int Team::id()const
    {
        return _id;
    }
}
