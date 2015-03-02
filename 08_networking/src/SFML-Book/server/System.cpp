#include <SFML-Book/server/System.hpp>

#include <SFML-Book/server/Component.hpp>
#include <SFML-Book/server/Team.hpp>
#include <SFML-Book/server/Game.hpp>
#include <SFML-Book/server/Entity.hpp>

#include <SFML-Book/common/random.hpp>

namespace book
{
    ///////////////////// SYS AI MAIN ///////////////////////
    SysAIMain::SysAIMain(Game& game) : _game(game)
    {
    }

    void SysAIMain::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompAIMain::Handle AI;
        CompTeam::Handle team;
        auto view = manager.getByComponents(AI,team);
        auto end = view.end();
        for(auto begin = view.begin();begin != end;++begin)
        {
            if(team->_team != nullptr)
            {
                AI->_elapsed += dt;
                while(AI->_elapsed > AI->_delta)
                {
                    AI->_elapsed -= AI->_delta;
                    team->_team->addGold(AI->_gold_amount);
                }
            }
        }
    }

    ///////////////////// SYS AI WARRIOR ///////////////////////
    bool isEnemy(const std::vector<Team*>& enemies,Team* t)
    {
        size_t size = enemies.size();
        for(size_t i=0;i<size;++i)
        {
            if(enemies[i] == t)
                return true;
        }
        return false;
    }

    SysAIWarrior::SysAIWarrior(Game& game) : _game(game)
    {
    }
    
    void SysAIWarrior::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompAIWarrior::Handle AI;
        CompTeam::Handle team;
        CompSkin::Handle skin;
        auto view = manager.getByComponents(AI,team,skin);
        auto end = view.end();
        
        for(auto begin = view.begin();begin != end;++begin)
        {
            AI->_elapsed += dt;

            if(AI->_elapsed < AI->_delta)
                continue;

            std::vector<Team*> teamEnemies = team->_team->getEnemies();

            //if no enemies
            if(teamEnemies.size() <=0)
                continue;

            if(AI->_enemyId == std::uint32_t(-1) or not manager.isValid(AI->_enemyId))
            { //random Team Qg

                int team_index = random(0,teamEnemies.size()-1);
                const std::vector<std::uint32_t>& ids = teamEnemies[team_index]->getQgIds();

                if(ids.size() <= 0)
                    continue;
                AI->_enemyId = ids[random(0,ids.size()-1)];
            }

            Entity& e = **begin;

            const sf::Vector2i myCoord = e.getCoord();
            const int range = AI->_range;

            //seach near me
            for(int x =-range; x<=range;++x)
            {
                int m =std::min(range,-x+range);

                for(int y = std::max(-range,-x-range);y<=m;++y)
                {
                    std::list<Entity*> l = _game.getByCoords(myCoord + sf::Vector2i(x,y));
                    for(Entity* e : l)
                    {
                        if(e->has<CompTeam>() and e->has<CompHp>()) //check its team
                        {
                            Team* t = e->component<CompTeam>()->_team;
                            if( isEnemy(teamEnemies,t))
                            {
                                AI->_enemyId = e->id();
                                goto end_search;
                            }
                        }
                    }
                }
            }
end_search: //exit nesteed loops
            if(not manager.isValid(AI->_enemyId))
            {
                AI->_enemyId = std::uint32_t(-1);
                continue;
            }


            //update path
            Entity& enemy = manager.get(AI->_enemyId);
            const sf::Vector2i coord = enemy.getCoord();
            const int distance = _game.getDistance(myCoord,coord);

            if(distance <= range) //next me
            {
                //shoot it
                AI->_elapsed = sf::Time::Zero;
                CompHp::Handle hp = enemy.component<CompHp>();
                hp->_hp -= AI->_hitPoint;

                Entity& me = **begin;

                _game.markEntityUpdated(enemy.id());
                _game.markEntityHitted(enemy.id(),me.id());
                _game.markEntityHit(me.id(),enemy.id());

                //win some gold
                if(hp->_hp <=0)
                {
                    team->_team->addGold(hp->_maxHp/50);
                }
                //no need to move more
                if(begin->has<CompAIFlyer>())
                {
                    begin->component<CompAIFlyer>()->_pathToTake = myCoord;
                }
                else if(begin->has<CompAIWalker>())
                {
                    begin->component<CompAIWalker>()->_pathToTake = myCoord;
                }
            }
            else
            {
                sf::Vector2i path = _game.getPath1(myCoord,coord);
                //move closer
                if(begin->has<CompAIFlyer>())
                {
                    begin->component<CompAIFlyer>()->_pathToTake = path;
                }
                else if(begin->has<CompAIWalker>())
                {
                    begin->component<CompAIWalker>()->_pathToTake = path;
                }

            }
        }
    }

    ///////////////////// SYS AI DEFENDER ///////////////////////
    SysAIDefender::SysAIDefender(Game& game) : _game(game)
    {
    }

    void SysAIDefender::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompAIDefender::Handle AI;
        CompTeam::Handle team;
        CompSkin::Handle skin;
        auto view = manager.getByComponents(AI,team,skin);
        auto end = view.end();
        
        for(auto begin = view.begin();begin != end;++begin)
        {
            AI->_elapsed += dt;
            if(AI->_elapsed < AI->_delta)
                continue;

            std::vector<Team*> teamEnemies = team->_team->getEnemies();

            //if no enemies
            if(teamEnemies.size() <=0)
                continue;

            std::uint32_t id = std::uint32_t(-1);

            Entity& e = **begin;
            const sf::Vector2i myCoord = e.getCoord();
            const int range = AI->_range;

            //seach near me
            for(int x =-range; x<=range;++x)
            {
                int m =std::min(range,-x+range);

                for(int y = std::max(-range,-x-range);y<=m;++y)
                {
                    std::list<Entity*> l = _game.getByCoords(myCoord + sf::Vector2i(x,y));
                    for(Entity* e : l)
                    {
                        if(e->has<CompTeam>() and e->has<CompHp>()) //check its team
                        {
                            Team* t = e->component<CompTeam>()->_team;
                            if( isEnemy(teamEnemies,t))
                            {
                                id = e->id();
                                goto end_search;
                            }
                        }
                    }
                }
            }
end_search: //exit nesteed loops
            if(not manager.isValid(id))
            {
                continue;
            }


            //update path
            Entity& enemy = manager.get(id);
            //shoot it
            AI->_elapsed = sf::Time::Zero;
            CompHp::Handle hp = enemy.component<CompHp>();
            hp->_hp -= AI->_hitPoint;

            Entity& me = **begin;

            _game.markEntityUpdated(enemy.id());
            _game.markEntityHitted(enemy.id(),me.id());
            _game.markEntityHit(me.id(),enemy.id());


            //win some gold
            if(hp->_hp <=0)
            {
                team->_team->addGold(hp->_maxHp/50);
            }
        }
    }

    ///////////////////// SYS AI SPAWNER ///////////////////////
    SysAISpawner::SysAISpawner(Game& game) : _game(game)
    {
    }

    void SysAISpawner::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompAISpawner::Handle AI;
        CompTeam::Handle team;
        CompSkin::Handle skin;
        auto view = manager.getByComponents(AI,team,skin);
        auto end = view.end();
        for(auto begin = view.begin();begin != end;++begin)
        {
            if(team->_team != nullptr)
            {
                AI->_elapsed += dt;
                const Entity& e = **begin;
                if(skin->_animationId == CompSkin::Stand)//if Stand
                {
                    if(AI->_elapsed > AI->_delta)
                    {
                        AI->_elapsed = sf::Time::Zero;
                        skin->_animationId = CompSkin::Spawn;
                        _game.markEntityUpdated(e.id());
                    }
                }
                else if(skin->_animationId == CompSkin::Spawn) //spawning
                {
                    if(AI->_elapsed > sf::seconds(1))
                    {
                        AI->_elapsed = sf::Time::Zero;
                        skin->_animationId = CompSkin::Stand;

                        _game.markEntityUpdated(e.id());
                        _game.markEntitySpawn(e.id());

                        auto team = e.component<CompTeam>();
                        auto AI = e.component<CompAISpawner>();
                        //create new
                        sf::Vector2i coord = e.getCoord();

                        for(int i=0;i<AI->_number;++i)
                        {
                            this->_game.createEntity(coord,team->_team,AI->_makeAs);
                        }
                    }
                }
            }
        }
    }

    ///////////////////// SYS AI WALKER ///////////////////////
    SysAIWalker::SysAIWalker(Game& game) :_game(game)
    {
    }
    void SysAIWalker::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompAIWalker::Handle AI;
        CompSkin::Handle skin;
        auto view = manager.getByComponents(AI,skin);
        auto end = view.end();

        const float seconds = dt.asSeconds();
        for(auto begin = view.begin();begin != end;++begin)
        {
            Entity& e = **begin;

            sf::Vector2f PosCurrent = e.getPosition();
            sf::Vector2i CoordCurrent = e.getCoord();

            sf::Vector2i CoordDest = AI->_pathToTake;
            if(CoordDest != CoordCurrent) //need to move
            {
                sf::Vector2f PosDest = _game.mapCoordsToPixel(CoordDest);

                //calulation of the diriction to take
                sf::Vector2f directon = PosDest - PosCurrent;
                //calculation of the distance
                const float distance = std::sqrt((directon.x*directon.x)+(directon.y*directon.y));
                const float frameDistance = AI->_speed * seconds;

                if(distance > frameDistance)
                {
                    sf::Vector2f nextPos = PosCurrent + directon*(frameDistance/distance);
                    _game.setPosition(**begin,CoordCurrent,PosCurrent,_game.mapPixelToCoords(nextPos),nextPos);
                }
                else
                {
                    _game.setPosition(**begin,CoordCurrent,PosCurrent,CoordDest,PosDest);
                    AI->_pathToTake = CoordCurrent;
                }

                if(directon.x >0) //unpdate skin direction
                {
                    skin->_animationId = CompSkin::MoveRight;
                }
                else
                {
                    skin->_animationId = CompSkin::MoveLeft;
                }
            }
        }
    }

    ///////////////////// SYS AI FLYER ///////////////////////
    SysAIFlyer::SysAIFlyer(Game& game) : _game(game)
    {
    }
    void SysAIFlyer::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompAIFlyer::Handle AI;
        CompSkin::Handle skin;
        auto view = manager.getByComponents(AI,skin);
        auto end = view.end();

        const float seconds = dt.asSeconds();
        for(auto begin = view.begin();begin != end;++begin)
        {
            Entity& e = **begin;

            sf::Vector2f PosCurrent = e.getPosition();
            sf::Vector2i CoordCurrent = e.getCoord();

            sf::Vector2i CoordDest = AI->_pathToTake;
            if(CoordDest != CoordCurrent) //need to move
            {
                sf::Vector2f PosDest = _game.mapCoordsToPixel(CoordDest);

                //calulation of the diriction to take
                sf::Vector2f directon = PosDest - PosCurrent;
                //calculation of the distance
                const float distance = std::sqrt((directon.x*directon.x)+(directon.y*directon.y));
                const float frameDistance = AI->_speed * seconds;

                if(distance > frameDistance)
                {
                    sf::Vector2f nextPos = PosCurrent + directon*(frameDistance/distance);
                    _game.setPosition(**begin,CoordCurrent,PosCurrent,_game.mapPixelToCoords(nextPos),nextPos);
                }
                else
                {
                    _game.setPosition(**begin,CoordCurrent,PosCurrent,CoordDest,PosDest);
                    AI->_pathToTake = CoordCurrent;
                }

                if(directon.x >0) //unpdate skin direction
                {
                    skin->_animationId = CompSkin::MoveRight;
                }
                else
                {
                    skin->_animationId = CompSkin::MoveLeft;
                }
            }
        }
    }
    
    ///////////////////// SYS AI HP ///////////////////////
    SysHp::SysHp(Game& game) : _game(game)
    {
    }
    void SysHp::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompHp::Handle hp;
        auto view = manager.getByComponents(hp);
        auto end = view.end();
        for(auto begin = view.begin();begin != end;++begin)
        {
            if(hp->_hp <= 0)
            {
                CompAIMain::Handle AI = begin->component<CompAIMain>();
                CompTeam::Handle team = begin->component<CompTeam>();
                if(AI.isValid() and team.isValid())
                {
                    team->_team->removeQgId(begin->id());
                }
                _game.destroyEntity((**begin).id());
            }
        }
    }
}
