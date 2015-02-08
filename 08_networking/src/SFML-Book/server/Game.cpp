#include <SFML-Book/server/Game.hpp>

namespace book
{
    Game::Game()
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
}
