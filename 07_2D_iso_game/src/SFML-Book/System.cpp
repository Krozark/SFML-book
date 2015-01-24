#include <SFML-Book/System.hpp>

#include <SFML-Book/Component.hpp>

namespace book
{
    
    void SysSkin::update(sfutils::EntityManager<Entity>& manager,const sf::Time& dt)
    {
        CompSkin::Handle skin;
        auto view = manager.getByComponents(skin);

        auto begin = view.begin();
        auto end = view.end();

        while(begin != end)
        {
            skin->_sprite.update(dt);
            ++begin;
        }
    }
}
