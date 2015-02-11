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
        _status(Status::StatusMainMenu),
        _mainMenu(_window,_client)
    {
        _window.setMouseCursorVisible(false);        
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

        _client.run();

        {
            sf::Packet event;
            event<<packet::GetListGame();
            _client.send(event);
        }

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
            else
            {
                switch(_status)
                {
                    case Status::StatusMainMenu :
                    {
                        _mainMenu.processEvent(event);
                    }break;
                    case Status::StatusGameMenu :
                    {
                    }break;
                    case Status::StatusDisconnected :
                    {
                    }break;
                }
            }
        }
        switch(_status)
        {
            case Status::StatusMainMenu :
            {
                _mainMenu.processEvents();
            }break;
            case Status::StatusGameMenu :
            {
            }break;
            case Status::StatusDisconnected :
            {
            }break;
        }
    }

    void Game::processNetworkEvents()
    {
        packet::NetworkEvent* msg;
        while(_client.pollEvent(msg))
        {
            if(msg->type() == FuncIds::IdDisconnected)
            {
                _isConnected = false;
                _status = StatusDisconnected;
            }
            else
            {
                switch(_status)
                {
                    case StatusMainMenu:
                    {
                        switch(msg->type())
                        {
                            case FuncIds::IdSetListGame :
                            {
                                packet::SetListGame* event = static_cast<packet::SetListGame*>(msg);
                                _mainMenu.fill(*event);
                            }break;
                            case FuncIds::IdJoinGameConfirmation :
                            {
                                packet::JoinGameConfirmation* event = static_cast<packet::JoinGameConfirmation*>(msg);
                                std::cout<<"Join game"<<std::endl;
                                const std::string& datas = event->getMapDatas();
                                _status = StatusGameMenu;
                            }break;
                            case FuncIds::IdJoinGameReject :
                            {
                                
                            }break;
                            default : break;
                        }
                    }break;
                    case StatusGameMenu :
                    {
                    }break;
                    case StatusDisconnected :
                    {
                    }break;
                }
            }

            delete msg;
        }
    }

    void Game::update(sf::Time deltaTime)
    {
        switch(_status)
        {
            case Status::StatusMainMenu :
            {
            }break;
            case Status::StatusGameMenu :
            {
            }break;
            case Status::StatusDisconnected :
            {
            }break;
        }
    }

    void Game::render()
    {
        _window.clear();
        switch(_status)
        {
            case Status::StatusMainMenu :
            {
                _window.draw(_mainMenu);
            }break;
            case Status::StatusGameMenu :
            {
            }break;
            case Status::StatusDisconnected :
            {
            }break;
        }
         _window.draw(_cursor);

        _window.display();
    }
}
