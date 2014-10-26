#include <SFML-Book/Game.hpp>
#include <SFML-Book/ActionMap.hpp>

#include <SFML-Book/Configuration.hpp>

#include <SFML-Book/Entity.hpp>

int main(int argc,char* argv[])
{
    book::Configuration::initialize();

    book::Game game;
    game.run();
    
    return 0;
}
