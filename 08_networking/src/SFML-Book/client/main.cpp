#include <SFML-Book/client/Client.hpp>

#include <SFML-Book/common/Packet.hpp>

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
    if(not client.connect(sf::IpAddress(ip),port,sf::seconds(5)))
        return 1;

    std::cout<<"Ok"<<std::endl;

    client.run();

    sf::Packet event;
    event<<book::packet::GetListGame();
    client.send(event);

    bool running = true;
    while(running)
    {
        while(client.pollEvent(event) and running)
        {
            book::packet::NetworkEvent* msg = book::packet::NetworkEvent::makeFromPacket(event);
            if(msg != nullptr)
            {
                std::cout<<"Client "<<client.id()<<" recive data of type : "<<msg->type()<<std::endl;
                switch(msg->type())
                {
                    case book::FuncIds::IdSetListGame :
                    {
                        book::packet::SetListGame* gameList = static_cast<book::packet::SetListGame*>(msg);
                        for(const book::packet::SetListGame::Game& game : gameList->list())
                        {
                            std::cout<<"id: "<<game.id<<" teams: "<<game.nbTeams<<" players: "<<game.nbPlayers<<std::endl;
                        }
                    }break;
                    case book::FuncIds::IdDisconnected :
                    {
                        running = false;
                    }break;
                    default : break;
                }
                delete msg;
            }
        }
    }

    client.stop();
    client.disconnect();
    client.wait();

    return 0;
}
