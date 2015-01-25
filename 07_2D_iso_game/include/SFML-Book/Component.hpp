#ifndef BOOK_COMPONENT_HPP
#define BOOK_COMPONENT_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Core.hpp>

#include <unordered_map>

#include <SFML-Book/Entity.hpp>

namespace book
{
    class Team;

    //add some gold periodicly
    struct CompAIMain : sfutils::Component<CompAIMain,Entity>
    {
        explicit CompAIMain(Team* team,int gold,const sf::Time& timeDelta);

        Team* _team;
        const int _gold_amount;
        const sf::Time _delta;
        sf::Time _elapsed;
    };

    struct CompAIWarrior : sfutils::Component<CompAIWarrior,Entity>
    {
    };

    struct CompAIDefender : sfutils::Component<CompAIDefender,Entity>
    {
    };

    struct CompAISpawner : sfutils::Component<CompAISpawner,Entity>
    {
    };

    struct CompTeam : sfutils::Component<CompTeam,Entity>
    {
        explicit CompTeam(Team* team);
        Team* _team;
    };

    struct CompSkin : sfutils::Component<CompSkin,Entity>
    {
        enum AnimationId : int{
            Stand,
            MoveLeft,
            MoveRight,
            SpawnLeft,
            SpawnRight,
            HitLeft,
            HitRight
        };

        explicit CompSkin(){};

        sfutils::AnimatedSprite _sprite; 
        std::unordered_map<int,sfutils::Animation*> _animations;
    };

    struct CompHp : sfutils::Component<CompHp,Entity>
    {
    };

    struct CompLeveler : sfutils::Component<CompLeveler,Entity>
    {
    };

}
#endif
