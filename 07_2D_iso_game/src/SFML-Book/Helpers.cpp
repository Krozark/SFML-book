#include <SFML-Book/Helpers.hpp>
#include <SFML-Book/Configuration.hpp>

#include <SFML-Book/Component.hpp>
#include <SFML-Book/Team.hpp>

namespace book
{
    
    void makeAsMain(Entity& entity,Team* team)
    {
        //add animation
        setAnimation(entity,Configuration::AnimMain,CompSkin::Stand,0.5,0.7,0.17,0.17);

        //add team
        setTeam(entity,team);

        //add AI
        entity.add<CompAIMain>(team,100,sf::seconds(10));

    }

    void setTeam(Entity& entity,Team* team)
    {
        if(team)
        {
            entity.add<CompTeam>(team);
            entity.component<CompSkin>()->_sprite.setColor(team->gui.getColor());
        }
    }

    void setAnimation(Entity& entity,int animationId,int animationMap,float ox,float oy,float sx,float sy)
    {
        CompSkin& skin = *entity.component<CompSkin>().get();
        sfutils::Animation& animation = Configuration::animations.get(animationId);

        skin._animations.emplace(animationMap,&animation);
        skin._sprite.setAnimation(skin._animations.at(animationMap));

        //resize to map size
        sf::IntRect rec = animation.getRect(0);
        skin._sprite.setOrigin(rec.width*ox,rec.height*oy);
        skin._sprite.setScale(sx,sy);
    }
}
