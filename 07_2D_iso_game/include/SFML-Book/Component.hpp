#ifndef BOOK_COMPONENT_HPP
#define BOOK_COMPONENT_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Core.hpp>

#include <unordered_map>

#include <SFML-Book/Entity.hpp>

namespace book
{
    class Team;

    struct CompAIMain : sfutils::Component<CompAIMain,Entity>
    {
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

}
#endif
