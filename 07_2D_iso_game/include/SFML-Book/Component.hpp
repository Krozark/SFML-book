#ifndef BOOK_COMPONENT_HPP
#define BOOK_COMPONENT_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Core.hpp>

#include <unordered_map>

#include <SFML-Book/Entity.hpp>

namespace book
{
    class Team;
    class Level;

    //add some gold periodicly
    struct CompAIMain : sfutils::Component<CompAIMain,Entity>
    {
        explicit CompAIMain(int gold,const sf::Time& timeDelta);

        const int _gold_amount;
        const sf::Time _delta;
        sf::Time _elapsed;
    };

    struct CompAIWarrior : sfutils::Component<CompAIWarrior,Entity>
    {
        explicit CompAIWarrior(int hitPoint,const sf::Time& timeDelta,int range);

        const int _hitPoint;
        const sf::Time _delta;
        sf::Time _elapsed;
        const int _range;
    };

    struct CompAIDefender : sfutils::Component<CompAIDefender,Entity>
    {
        explicit CompAIDefender(int hitPoint,const sf::Time& timeDelta,int range);

        const int _hitPoint;
        const sf::Time _delta;
        sf::Time _elapsed;
        const int _range;
    };

    struct CompAISpawner : sfutils::Component<CompAISpawner,Entity>
    {
        using FuncType = std::function<void(Entity& entity,Team* team,Level& level)>;
        typedef void (*FuncType_onSpawn)(Level& level,const sf::Vector2i& pos);

        explicit CompAISpawner(FuncType makeAs,int number,const sf::Time& timeDelta,FuncType_onSpawn onSpawn = [](Level&,const sf::Vector2i&){});
        
        FuncType _makeAs;
        const int _number;
        const sf::Time _delta;
        sf::Time _elapsed;
        FuncType_onSpawn _OnSpawn;

    };

    struct CompAIWalker : sfutils::Component<CompAIWalker,Entity>
    {
        explicit CompAIWalker(float speed);

        const float _speed;
        sf::Vector2i _pathToTake;
    };

    struct CompAIFlyer : sfutils::Component<CompAIFlyer,Entity>
    {
        explicit CompAIFlyer(float speed);

        const float _speed;
        sf::Vector2i _pathToTake;
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
            Spawn,
            MoveLeft,
            MoveRight,
            HitLeft,
            HitRight
        };

        explicit CompSkin(){};

        sfutils::AnimatedSprite _sprite; 
        std::unordered_map<int,sfutils::Animation*> _animations;
    };

    struct CompHp : sfutils::Component<CompHp,Entity>
    {
        explicit CompHp(int hp);

        void update(const sf::Vector2f& pos);

        void draw(sf::RenderTarget& target,sf::RenderStates states);

        sf::RectangleShape _shape_hp;
        sf::RectangleShape _shape_max_hp;

        int _hp;
        const int _maxHp;

        static const float _height;
        static const float _width;
    };


    struct CompUpgradable : sfutils::Component<CompUpgradable,Entity>
    {
    };

    struct CompEffect : sfutils::Component<CompEffect,Entity>
    {
    };

    struct CompBuildArea : sfutils::Component<CompBuildArea,Entity>
    {
        explicit CompBuildArea(int range);

        int _range;
    };
}
#endif
