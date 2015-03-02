
#include <SFML-Book/server/Team.hpp>
#include <SFML-Book/server/Game.hpp>

namespace book
{
    Team::Team(int id,const sf::Color& color,int gold,Game& game) : _isAlive(true),_id(id), _gold(gold), _QGId(0), _color(color), _game(game)
    {
    }

    void Team::addGold(int amount)
    {
        _gold += amount;
        _game.markTeamUpdated(_id);
    }

    int Team::getGold()const
    {
        return _gold;
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
        _isAlive = _QGId.size()>0;
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

    bool Team::isGameOver()const
    {
        return _isAlive;
    }

}
