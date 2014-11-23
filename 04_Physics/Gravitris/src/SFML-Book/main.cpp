#include <SFML-Book/Game.hpp>

int main(int argc,char* argv[])
{
    book::Game game(10,20);
    game.run(30,60);
    return 0;
}
