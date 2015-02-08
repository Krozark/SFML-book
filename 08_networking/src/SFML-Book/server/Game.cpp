#include <SFML-Book/server/Game.hpp>

namespace book
{
    int Game::_numberOfCreations = 0;
    
    Game::Game() : _id(++_numberOfCreations)
    {
    }

    std::size_t Game::getTeamCount()
    {
        sf::Lock guard(_teamMutex);
        return _teams.size();
    }

    std::size_t Game::getPalyersCount()
    {
        sf::Lock guard(_clientsMutex);
        return _clients.size();
    }

    int Game::id()const
    {
        return _id;
    }
}
