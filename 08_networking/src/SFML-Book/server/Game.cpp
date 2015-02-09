#include <SFML-Book/server/Game.hpp>

namespace book
{
    int Game::_numberOfCreations = 0;
    
    Game::Game() : _id(++_numberOfCreations)
    {
    }

    int Game::getTeamCount()
    {
        sf::Lock guard(_teamMutex);
        return _teams.size();
    }

    int Game::getPalyersCount()
    {
        sf::Lock guard(_clientsMutex);
        return _clients.size();
    }

    int Game::id()const
    {
        return _id;
    }
}
