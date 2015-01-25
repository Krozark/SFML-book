#include <SFML-Book/System.hpp>

#include <SFML-Book/Component.hpp>
#include <SFML-Book/Team.hpp>
#include <SFML-Book/Level.hpp>

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
        
        static sf::Vector2i neighbors[] = {{1,0},{1,1},{0,-1},{-1,0},{-1,1},{0,1}};
        //return Hex(q + d[0], r + d[1])

        for(auto begin = view.begin();begin != end;++begin)
        {
            if(team->_team != nullptr)
            {
                auto teamEnemies = team->_team->getEnemies();
                sf::Vector2i myPosition = _level.mapPixelToCoords(skin->_sprite.getPosition());

                if(AI->_target == std::uint32_t(-1)) //search new enemy
                {
                    if(teamEnemies.size()>0)
                    {
                        AI->_target = teamEnemies.front()->getQgId();
                        //update path
                        Entity& QG = manager.get(AI->_target);
                        sf::Vector2f QGPos = QG.component<CompSkin>()->_sprite.getPosition();
                        std::list<sf::Vector2i> path = _level.getPath(myPosition,_level.mapPixelToCoords(QGPos));

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
                if(manager.isValid(AI->_target))
                {
                    Entity* enemie = nullptr;
                    //look for enemies around my position
                    for(auto& pos : neighbors)
                    {
                        std::list<Entity*> l = _level.getByCoords(myPosition + pos);
                        for(Entity* e : l)
                        {
                            if(e->has<CompTeam>() and e->has<CompHp>()) //chack its team
                            {
                                Team* t = e->component<CompTeam>()->_team;
                                for(Team* team : teamEnemies) //if team is enemy, save it
                                {
                                    if(t == team)
                                    {
                                        enemie = e;
                                        goto end_search;
                                    }
                                }
                            }
                        }
                    }
end_search:
                    AI->_elapsed += dt;
                    if(enemie != nullptr)
                    {
                        //shoot it
                        if(AI->_elapsed > AI->_delta)
                        {
                            AI->_elapsed = sf::Time::Zero;
                            enemie->component<CompHp>()->_hp -= AI->_hitPoint;
                        }
                    }
                }
                else
                {
                    AI->_target = std::uint32_t(-1);
                }
            }
        }
    }

    ///////////////////// SYS AI DEFENDER ///////////////////////
    void SysAIDefender::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
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
                            coord.y+=1;
                            Entity& newEntity = this->_level.createEntity(coord);
                            //init with callback
                            AI->_makeAs(newEntity,team->_team);
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
            if(AI->_pathToTake.size() > 0) //need to move
            {
                sf::Vector2f PosCurrent = skin->_sprite.getPosition();
                //sf::Vector2i CoordCurrent = _level.mapPixelToCoords(PosCurrent);

                sf::Vector2i CoordDest = AI->_pathToTake.front();
                sf::Vector2f PosDest = _level.mapCoordsToPixel(CoordDest);

                //calulation of the diriction to take
                sf::Vector2f directon = PosDest - PosCurrent;
                //calculation of the distance
                const float distance = std::sqrt((directon.x*directon.x)+(directon.y*directon.y));
                const float frameDistance = AI->_speed * seconds;

                if(distance < frameDistance)
                {
                    skin->_sprite.setPosition(PosCurrent + directon*(frameDistance/distance));
                }
                else
                {
                    skin->_sprite.setPosition(PosDest);
                    AI->_pathToTake.pop_front();
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
            if(AI->_pathToTake.size() > 0) //need to move
            {
                sf::Vector2f PosCurrent = skin->_sprite.getPosition();
                //sf::Vector2i CoordCurrent = _level.mapPixelToCoords(PosCurrent);

                sf::Vector2i CoordDest = AI->_pathToTake.front();
                sf::Vector2f PosDest = _level.mapCoordsToPixel(CoordDest);


                //calulation of the diriction to take
                sf::Vector2f directon = PosDest - PosCurrent;
                //calculation of the distance
                const float distance = std::sqrt((directon.x*directon.x)+(directon.y*directon.y));
                const float frameDistance = AI->_speed * seconds;

                if(distance > frameDistance)
                {
                    skin->_sprite.setPosition(PosCurrent + directon*(frameDistance/distance));
                }
                else
                {
                    skin->_sprite.setPosition(PosDest);
                    AI->_pathToTake.pop_front();
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
    void SysHp::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompHp::Handle hp;
        auto view = manager.getByComponents(hp);
        auto end = view.end();
        for(auto begin = view.begin();begin != end;++begin)
        {
            if(hp->_hp <= 0)
                begin->remove();
        }
    }
}
