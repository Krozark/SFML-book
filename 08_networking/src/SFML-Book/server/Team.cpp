
#include <SFML-Book/server/Team.hpp>

namespace book
{
    int Team::_numberOfCreations = 0;

    Team::Team(const sf::Color& color) : isAlive(true),_id(_numberOfCreations++), _gold(0), _QGId(0), _color(color)
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
        std::size_t size = _QGId.size();
        std::size_t i=0;
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

    const sf::Color& Team::getColor()const
    {
        return _color;
    }

    void Team::add(Client* client)
    {
        _clients.emplace_back(client);
    }

    void Team::remove(Client* client)
    {
        _clients.remove(client);
    }

    const std::list<Client*>& Team::getClients()const
    {
        return _clients;
    }
}
