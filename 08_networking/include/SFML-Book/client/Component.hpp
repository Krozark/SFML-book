#ifndef BOOK_COMPONENT_HPP
#define BOOK_COMPONENT_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Core.hpp>

#include <unordered_map>

#include <SFML-Book/client/Entity.hpp>

namespace book
{
    class Team;
    class Level;

    struct CompAISpawner : sfutils::Component<CompAISpawner,Entity>
    {
        using FuncType = std::function<void(Entity& entity,Team* team,Level& level)>;
        typedef void (*FuncType_onSpawn)(Level& level,const sf::Vector2i& pos);

        explicit CompAISpawner(FuncType_onSpawn onSpawn = [](Level&,const sf::Vector2i&){});
        
        FuncType_onSpawn _onSpawn;
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
        explicit CompHp(int hp,int maxHp);

        void update(const sf::Vector2f& pos);

        void draw(sf::RenderTarget& target,sf::RenderStates states);

        sf::RectangleShape _shapeHp;
        sf::RectangleShape _shapeMaxHp;

        int _hp;
        const int _maxHp;

        static const float _height;
        static const float _width;
    };


    struct CompUpgradable : sfutils::Component<CompUpgradable,Entity>
    {
    };

    struct CompBuildArea : sfutils::Component<CompBuildArea,Entity>
    {
        explicit CompBuildArea(int range);

        int _range;
    };
}
#endif
