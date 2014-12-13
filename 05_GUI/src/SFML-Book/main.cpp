#include <SFML-Book/Game.hpp>
#include <SFML-Book/Configuration.hpp>

int main(int argc,char* argv[])
{
    book::Configuration::initialize();

    book::Game game(600,900,10,20);
    game.run(30,60);
    return 0;
}
