#include <SFML-Book/client/Client.hpp>

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


    std::cout<<"Client start on port "<<port<<std::endl;

    book::Client client;
    if(client.connect(sf::IpAddress(ip),port,sf::seconds(5)))
    {
        std::cout<<"Ok"<<std::endl;
    }

    sf::sleep(sf::seconds(1));

    return 0;
}
