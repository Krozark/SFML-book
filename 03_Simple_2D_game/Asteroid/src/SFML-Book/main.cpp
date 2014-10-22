#include <SFML-Book/Game.hpp>
#include <SFML-Book/ActionMap.hpp>

#include <SFML-Book/Configuration.hpp>

int main(int argc,char* argv[])
{
    book::Configuration::initialize();

    book::Game game;
    game.runWithMinimumTimeSteps();

    return 0;
}
