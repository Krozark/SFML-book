#include <SFML-utils/Map.hpp>

#include <iostream>

#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Game.hpp>

int main(int argc,char* argv[])
{
    book::Configuration::initialize();

    book::Game game(1600,900);
    game.load("./media/map.json");
    game.run();

    return 0;
};
