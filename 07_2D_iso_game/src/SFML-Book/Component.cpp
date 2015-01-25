#include <SFML-Book/Component.hpp>

namespace book
{
    CompAIMain::CompAIMain(Team* team,int gold,const sf::Time& timeDelta) : _team(team), _gold_amount(gold),_delta(timeDelta), _elapsed(sf::Time::Zero)
    {
    }

    CompTeam::CompTeam(Team* team) : _team(team)
    {
    }
}
