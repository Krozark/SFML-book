#include <SFML-Book/System.hpp>

#include <SFML-Book/Component.hpp>
#include <SFML-Book/Team.hpp>

namespace book
{
    void SysAiMain::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompAIMain::Handle AI;
        auto view = manager.getByComponents(AI);
        auto end = view.end();
        for(auto begin = view.begin();begin != end;++begin)
        {
            if(AI->_team != nullptr)
            {
                AI->_elapsed += dt;
                while(AI->_elapsed > AI->_delta)
                {
                    AI->_elapsed -= AI->_delta;
                    AI->_team->addGold(AI->_gold_amount);
                }
            }
        }
    }
    
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
}
