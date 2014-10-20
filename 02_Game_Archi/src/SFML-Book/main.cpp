#include <SFML-Book/Game.hpp>
#include <SFML-Book/ActionMap.hpp>

int main(int argc,char* argv[])
{
    book::Player::setDefaultsInputs();

    book::Game game;
    game.runWithMinimumTimeSteps();

    return 0;
}
