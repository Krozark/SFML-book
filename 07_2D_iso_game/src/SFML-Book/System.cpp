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
    void SysAIWarrior::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
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
    void SysAIWalker::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
    }

    ///////////////////// SYS AI FLYER ///////////////////////
    void SysAIFlyer::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
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
