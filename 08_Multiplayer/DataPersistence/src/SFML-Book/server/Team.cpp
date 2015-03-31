
#include <SFML-Book/server/Team.hpp>


M2M_REGISTER(Team,_enemies,Team,"Team_enemies","team_id","enemi_id")
REGISTER(Team,"Team",\
         _isAlive,"isAlive",\
         _id,"id",\
         _gold,"gold",\
         _colorChar,"color",\
         _game,"game_id")
Team::Team() : _isAlive(Team::$_isAlive),
    _id(Team::$_id),
    _gold(Team::$_gold),
    _colorChar(Team::$_colorChar),
    _game(Team::$_game),
    _enemies(*this)
{
    _isAlive.registerAttr(*this);
    _id.registerAttr(*this);
    _gold.registerAttr(*this);
    _colorChar.registerAttr(*this);
    _game.registerAttr(*this);
}

Team::Team(int id,const sf::Color& color,int gold,Game::type_ptr game) : Team()
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
    _enemies.add(team);
}

const Team::result_type Team::getEnemies()
{
    auto r = _enemies.all();
    return r;

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

void Team::after_load()
{
    std::string c = _colorChar.value().c_str();
    _color.r = c[0];
    _color.g = c[1];
    _color.b = c[2];
    _color.a = c[3];
    
}

void Team::before_save()
{
    unsigned char c[4] = {_color.r,_color.g,_color.b,_color.a};
    _colorChar = (char*)c;
}

void Team::before_update()
{
    before_save();
}

