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
        sfutils::Animation& animation = Configuration::animations.get(Configuration::AnimMain);

        skin._animations.emplace(CompSkin::Stand,&animation);
        skin._sprite.setAnimation(skin._animations.at(CompSkin::Stand));

        //resize to map size
        sf::IntRect rec = animation.getRect(0);
        skin._sprite.setOrigin(rec.width*0.5,rec.height*0.7);
        skin._sprite.setScale(0.1,0.1);

        //add team
        e.add<CompTeam>(team);

        //add to layer
        layer.add(&e);

        return id;
    }
}
