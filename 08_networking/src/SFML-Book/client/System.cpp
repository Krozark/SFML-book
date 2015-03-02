#include <SFML-Book/client/System.hpp>

#include <SFML-Book/client/Component.hpp>
#include <SFML-Book/client/Team.hpp>
#include <SFML-Book/client/Level.hpp>

namespace book
{
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
            CompSkin::Handle skin = begin->component<CompSkin>();
            if(skin.isValid())
            {
                hp->update(skin->_sprite.getPosition());
            }
        }
    }
    
}
