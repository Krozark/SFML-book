#include <SFML-Book/System.hpp>

#include <SFML-Book/Component.hpp>
#include <SFML-Book/Team.hpp>
#include <SFML-Book/Level.hpp>
#include <SFML-Book/Helpers.hpp>

namespace book
{
    ///////////////////// SYS AI MAIN ///////////////////////
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

    SysAIWarrior::SysAIWarrior(Level& level) : _level(level)
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

            std::uint32_t id = std::uint32_t(-1);
            const std::vector<std::uint32_t>& ids = teamEnemies[0]->getQgIds();

            if(ids.size() <= 0)
                continue;

            id = ids[0];


            const sf::Vector2i myPosition = _level.mapPixelToCoords(skin->_sprite.getPosition());
            const int range = AI->_range;

            //seach near me
            for(int x =-range; x<=range;++x)
            {
                int m =std::min(range,-x+range);

                for(int y = std::max(-range,-x-range);y<=m;++y)
                {
                    std::list<Entity*> l = _level.getByCoords(myPosition + sf::Vector2i(x,y));
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
            const sf::Vector2f pos = enemy.component<CompSkin>()->_sprite.getPosition();
            const sf::Vector2i coord = _level.mapPixelToCoords(pos);
            const int distance = _level.getDistance(myPosition,coord);

            if(distance <= range) //next me
            {
                //shoot it
                AI->_elapsed = sf::Time::Zero;
                CompHp::Handle hp = enemy.component<CompHp>();
                hp->_hp -= AI->_hitPoint;

                Entity& me = **begin;

                if(enemy.onHitted != nullptr)
                    enemy.onHitted(enemy,coord,me,myPosition,_level);
                if(me.onHit != nullptr)
                    me.onHit(me,myPosition,enemy,coord,_level);


                //win some gold
                if(hp->_hp <=0)
                {
                    team->_team->addGold(hp->_maxHp/50);
                }
                //no need to move more
                if(begin->has<CompAIFlyer>())
                {
                    begin->component<CompAIFlyer>()->_pathToTake = myPosition;
                }
                else if(begin->has<CompAIWalker>())
                {
                    begin->component<CompAIWalker>()->_pathToTake = myPosition;
                }
            }
            else
            {
                sf::Vector2i path = _level.getPath1(myPosition,coord);
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
    SysAIDefender::SysAIDefender(Level& level) : _level(level)
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

            const sf::Vector2i myPosition = _level.mapPixelToCoords(skin->_sprite.getPosition());
            const int range = AI->_range;

            //seach near me
            for(int x =-range; x<=range;++x)
            {
                int m =std::min(range,-x+range);

                for(int y = std::max(-range,-x-range);y<=m;++y)
                {
                    std::list<Entity*> l = _level.getByCoords(myPosition + sf::Vector2i(x,y));
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
            const sf::Vector2f pos = enemy.component<CompSkin>()->_sprite.getPosition();
            const sf::Vector2i coord = _level.mapPixelToCoords(pos);

            //shoot it
            AI->_elapsed = sf::Time::Zero;
            CompHp::Handle hp = enemy.component<CompHp>();
            hp->_hp -= AI->_hitPoint;

            Entity& me = **begin;

            if(enemy.onHitted != nullptr)
                enemy.onHitted(enemy,coord,me,myPosition,_level);
            if(me.onHit != nullptr)
                me.onHit(me,myPosition,enemy,coord,_level);


            //win some gold
            if(hp->_hp <=0)
            {
                team->_team->addGold(hp->_maxHp/50);
            }
        }
    }

    ///////////////////// SYS AI SPAWNER ///////////////////////
    SysAISpawner::SysAISpawner(Level& level) : _level(level)
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
                if(skin->_sprite.getAnimation() == skin->_animations.at(CompSkin::Stand))//if Stand
                {
                    AI->_elapsed += dt;
                    if(AI->_elapsed > AI->_delta)
                    {
                        AI->_elapsed = sf::Time::Zero;
                        skin->_sprite.setAnimation(skin->_animations.at(CompSkin::Spawn));
                        skin->_sprite.setRepeate(3);
                        skin->_sprite.setLoop(false);

                        std::uint32_t id = begin->id();

                        skin->_sprite.on_finished = [this,id,&manager](){
                            const Entity& e = manager.get(id);
                            auto skin = e.component<CompSkin>();
                            auto team = e.component<CompTeam>();
                            auto AI = e.component<CompAISpawner>();
                            //reset animation
                            skin->_sprite.setAnimation(skin->_animations.at(CompSkin::Stand));
                            skin->_sprite.setLoop(true);
                            skin->_sprite.play();
                            //create new
                            sf::Vector2f pos = skin->_sprite.getPosition();
                            sf::Vector2i coord = this->_level.mapPixelToCoords(pos);
                            for(int i=0;i<AI->_number;++i)
                            {
                                Entity& newEntity = this->_level.createEntity(coord);
                                //init with callback
                                AI->_makeAs(newEntity,team->_team,this->_level);
                                AI->_OnSpawn(this->_level,coord);
                            }
                        };
                    }
                }
            }
        }
    }

    ///////////////////// SYS AI WALKER ///////////////////////
    SysAIWalker::SysAIWalker(Level& level) :_level(level)
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
            sf::Vector2f PosCurrent = skin->_sprite.getPosition();
            sf::Vector2i CoordCurrent = _level.mapPixelToCoords(PosCurrent);

            sf::Vector2i CoordDest = AI->_pathToTake;
            if(CoordDest != CoordCurrent) //need to move
            {
                sf::Vector2f PosDest = _level.mapCoordsToPixel(CoordDest);

                //calulation of the diriction to take
                sf::Vector2f directon = PosDest - PosCurrent;
                //calculation of the distance
                const float distance = std::sqrt((directon.x*directon.x)+(directon.y*directon.y));
                const float frameDistance = AI->_speed * seconds;

                if(distance > frameDistance)
                {
                    sf::Vector2f nextPos = PosCurrent + directon*(frameDistance/distance);
                    skin->_sprite.setPosition(nextPos);
                    _level.setPosition(**begin,CoordCurrent,_level.mapPixelToCoords(nextPos));
                }
                else
                {
                    skin->_sprite.setPosition(PosDest);
                    _level.setPosition(**begin,CoordCurrent,CoordDest);
                    AI->_pathToTake = CoordCurrent;
                }

                if(directon.x >0) //unpdate skin direction
                {
                    skin->_sprite.setAnimation(skin->_animations.at(CompSkin::MoveRight));
                }
                else
                {
                    skin->_sprite.setAnimation(skin->_animations.at(CompSkin::MoveLeft));
                }
            }
        }
    }

    ///////////////////// SYS AI FLYER ///////////////////////
    SysAIFlyer::SysAIFlyer(Level& level) : _level(level)
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
            sf::Vector2f PosCurrent = skin->_sprite.getPosition();
            sf::Vector2i CoordCurrent = _level.mapPixelToCoords(PosCurrent);

            sf::Vector2i CoordDest = AI->_pathToTake;
            if(CoordDest != CoordCurrent) //need to move
            {
                sf::Vector2f PosDest = _level.mapCoordsToPixel(CoordDest);

                //calulation of the diriction to take
                sf::Vector2f directon = PosDest - PosCurrent;
                //calculation of the distance
                const float distance = std::sqrt((directon.x*directon.x)+(directon.y*directon.y));
                const float frameDistance = AI->_speed * seconds;

                if(distance > frameDistance)
                {
                    sf::Vector2f nextPos = PosCurrent + directon*(frameDistance/distance);
                    skin->_sprite.setPosition(nextPos);
                    _level.setPosition(**begin,CoordCurrent,_level.mapPixelToCoords(nextPos));
                }
                else
                {
                    skin->_sprite.setPosition(PosDest);
                    _level.setPosition(**begin,CoordCurrent,CoordDest);
                    AI->_pathToTake = CoordCurrent;
                }

                if(directon.x >0) //unpdate skin direction
                {
                    skin->_sprite.setAnimation(skin->_animations.at(CompSkin::MoveRight));
                }
                else
                {
                    skin->_sprite.setAnimation(skin->_animations.at(CompSkin::MoveLeft));
                }
            }
        }
    }
    
    ///////////////////// SYS AI SKIN ///////////////////////
    void SysSkin::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompSkin::Handle skin;
        auto view = manager.getByComponents(skin);
        auto end = view.end();
        for(auto begin = view.begin();begin != end;++begin)
        {
            skin->_sprite.update(dt);
        }
    }

    ///////////////////// SYS AI HP ///////////////////////
    SysHp::SysHp(Level& level) : _level(level)
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
                _level.destroyEntity(**begin);
            }
            else
            {
                CompSkin::Handle skin = begin->component<CompSkin>();
                if(skin.isValid())
                {
                    hp->update(skin->_sprite.getPosition());
                }
            }
        }
    }
    
    ////////////////// EFFECTS //////////////////////
    SysEffect::SysEffect(Level& level) : _level(level)
    {
    }
    void SysEffect::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompEffect::Handle effect;
        CompSkin::Handle skin;
        auto view = manager.getByComponents(effect,skin);

        auto end = view.end();
        for(auto begin = view.begin();begin != end;++begin)
        {
            if(skin->_sprite.getStatus() != sfutils::AnimatedSprite::Status::Playing)
            {
                _level.destroyEntity(**begin);
            }
        }
    }
}
