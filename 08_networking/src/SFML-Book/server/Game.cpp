#include <SFML-Book/server/Game.hpp>

#include <SFML-Book/server/Client.hpp>
#include <SFML-Book/server/Team.hpp>

namespace book
{
    int Game::_numberOfCreations = 0;
    
    Game::Game() : _id(++_numberOfCreations)
    {
    }

    Game::~Game()
    {
        for(Client* client: _clients)
            delete client;

        for(Team* team : _teams)
            delete team;
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
