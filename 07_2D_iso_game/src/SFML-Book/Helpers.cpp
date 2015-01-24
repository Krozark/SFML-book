#include <SFML-Book/Helpers.hpp>
#include <SFML-Book/Configuration.hpp>

#include <SFML-Book/Component.hpp>

namespace book
{
    
    std::uint32_t makeMain(sfutils::EntityManager<Entity>& manager,sfutils::Layer<sfutils::HexaIso,Entity*>& layer,Team* team)
    {
        std::uint32_t id = manager.create(); 
        Entity& e= manager.get(id);
        //add animation
        CompSkin& skin = *e.component<CompSkin>().get();
        skin._animations.emplace(CompSkin::Stand,&Configuration::animations.get(Configuration::AnimMain));
        skin._sprite.setAnimation(skin._animations.at(CompSkin::Stand));
        
        //add team
        e.add<CompTeam>(team);

        //add to layer
        layer.add(&e);

        return id;
    }
}
