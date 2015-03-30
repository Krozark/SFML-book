
#include <SFML-Book/server/Team.hpp>
#include <SFML-Book/server/Game.hpp>

REGISTER_AND_CONSTRUCT(Team,"Team",\
                       _isAlive,"isAlive",\
                       _id,"id",\
                       _gold,"gold")

Team::Team(int id,const sf::Color& color,int gold,book::Game* game) : Team()
{
    _isAlive = true;
    _id = id;
    _gold = gold;
    _color = color;
    _game = game;
}

void Team::addGold(int amount)
{
    _gold += amount;
    _game->markTeamUpdated(_id);
}

int Team::getGold()const
{
    return _gold.value();
}

void Team::addEnemy(Team::type_ptr team)
{
    _enemies.emplace_back(team);
}

const std::vector<Team::type_ptr>& Team::getEnemies()const
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
    return _id.value();
}

const sf::Color& Team::getColor()const
{
    return _color;
}

void Team::add(book::Client* client)
{
    _clients.emplace_back(client);
}

void Team::remove(book::Client* client)
{
    _clients.remove(client);
}

const std::list<book::Client*>& Team::getClients()const
{
    return _clients;
}

bool Team::isGameOver()const
{
    return _isAlive.value();
}

