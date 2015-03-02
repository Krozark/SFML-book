#include <SFML-Book/client/Game.hpp>

#include <SFML-Book/common/Configuration.hpp>


#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
    int port = 5678;
    std::string ip = "127.0.0.1";

    std::cout<<"Usage is : "<<argv[0]<<" [ip] [port]"<<std::endl;

    if(argc > 1)
        ip = argv[1];

    if(argc >2 )
        port = std::atoi(argv[2]);

    book::Configuration::initialize();


    std::cout<<"Client start on adresse "<<ip<<":"<<port<<std::endl;

    book::Game game;
    if(not game.connect(sf::IpAddress(ip),port,sf::seconds(5)))
        return 1;

    std::cout<<"Ok"<<std::endl;

    game.run();

    return 0;
}
