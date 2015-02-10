#include <SFML-Book/client/Game.hpp>

#include <SFML-Book/common/FuncIds.hpp>
#include <SFML-Book/common/Packet.hpp>
#include <SFML-Book/common/Configuration.hpp>


#include <iostream>


namespace book
{
    Game::Game(int X, int Y): 
        _window(sf::VideoMode(X,Y),"08 Networking"),        
        _cursor(Configuration::textures.get(Configuration::TexCursor)),        
        _isConnected(false),
        _status(Status::MainMenu)
    {
    }

    Game::~Game()
    {
        _client.stop();
        _client.disconnect();
        _client.wait();
    }

    bool Game::connect(const sf::IpAddress& ip, unsigned short port,sf::Time timeout)
    {
        _isConnected = _client.connect(ip,port,timeout);
        return _isConnected;
    }

    void Game::run(int frame_per_seconds)
    {
        if(not _isConnected)
            return;

        /*{
            sf::Packet event;
            event<<packet::GetListGame();
            _client.send(event);
        }*/

        sf::Clock clock;
        sf::Time timeSinceLastUpdate;
        sf::Time TimePerFrame = sf::seconds(1.f/frame_per_seconds);

        while (_window.isOpen())
        {
            bool repaint = false;

            processNetworkEvents();
            processEvents();

            //fix time delta between frames
            sf::Time delta = clock.restart();
            timeSinceLastUpdate += delta;
            if(timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                repaint = true;
                update(TimePerFrame);
            }

            if(repaint)
                render();
        }
    }

    void Game::processEvents()
    {
        sf::Event event;
        while(_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape))
            {
                _window.close();
            }
        }
    }

    void Game::processNetworkEvents()
    {
        packet::NetworkEvent* msg;
        while(_client.pollEvent(msg))
        {
            switch(msg->type())
            {
                case FuncIds::IdSetListGame :
                {
                    packet::SetListGame* gameList = static_cast<packet::SetListGame*>(msg);
                    for(const packet::SetListGame::Game& game : gameList->list())
                    {
                        std::cout<<"id: "<<game.id<<" teams: "<<game.nbTeams<<" players: "<<game.nbPlayers<<std::endl;
                    }
                }break;
                case FuncIds::IdJoinGameConfirmation :
                {
                    std::cout<<"Join game"<<std::endl;
                }break;
                case FuncIds::IdDisconnected :
                {
                    _isConnected = false;
                }break;
                default : break;
            }
            delete msg;
        }
    }

    void Game::update(sf::Time deltaTime)
    {
    }

    void Game::render()
    {
        _window.clear();
        _window.display();
    }
}
