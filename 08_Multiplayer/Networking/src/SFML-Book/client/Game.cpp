#include <SFML-Book/client/Game.hpp>

#include <SFML-Book/client/Component.hpp>

#include <SFML-Book/common/FuncIds.hpp>
#include <SFML-Book/common/Packet.hpp>
#include <SFML-Book/common/Configuration.hpp>

#include <iostream>
#include <sstream>


namespace book
{
    Game::Game(int X, int Y): 
        _asFocus(true),
        _window(sf::VideoMode(X,Y),"08 Networking"),        
        _cursor(Configuration::textures.get(Configuration::TexCursor)),        
        _isConnected(false),
        _status(Status::StatusMainMenu),
        _mainMenu(_window,_client),
        _gameMenu(_window,_client,_team),
        _level(nullptr),
        _team(-1)
    {
        _window.setMouseCursorVisible(false);        

        _onPickup = [this](std::uint32_t id,sf::Vector2i coord)
        {
            if(_level)
            {
                Entity* e = _level->entityManager().getPtr(id);
                if(e->has<CompTeam>())
                {
                    CompTeam::Handle team = e->component<CompTeam>();
                    if(team->_team->id() == _team)
                    {
                        _gameMenu.setSelected(id);
                    }
                }
            }
        };
    }

    Game::~Game()
    {
        delete _level;

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

            //fix time delta between frames
            sf::Time delta = clock.restart();
            timeSinceLastUpdate += delta;
            if(timeSinceLastUpdate > TimePerFrame)
            {
                processEvents();
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
            else if(event.type == sf::Event::GainedFocus)
                _asFocus = true;
            else if(event.type == sf::Event::LostFocus)
                _asFocus = false;
            else
            {
                switch(_status)
                {
                    case Status::StatusMainMenu :
                    {
                        _mainMenu.processEvent(event);
                    }break;
                    case Status::StatusInGame :
                    {
                        if(not _gameMenu.processEvent(event))
                            _level->processEvent(event);

                    }break;
                    case Status::StatusDisconnected :
                    {
                    }break;
                }
            }
        }
        if(_asFocus)
        {
            switch(_status)
            {
                case Status::StatusMainMenu :
                {
                    _mainMenu.processEvents();
                }break;
                case Status::StatusInGame :
                {
                    _gameMenu.processEvents();
                    _level->processEvents();
                }break;
                case Status::StatusDisconnected :
                {
                }break;
            }
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

                                std::stringstream ss;
                                ss<<datas;

                                _level = new Level(_window,event->getTeamId(),ss,datas);
                                _level->onPickup = _onPickup;

                                if(_level != nullptr)
                                {
                                    _team = event->getTeamId();
                                    for(const packet::JoinGameConfirmation::Data& data : event->getTeamInfo())
                                    {
                                        _level->_teamInfo.emplace(data.team,Team(data.team,data.color));

                                        if(data.team == _team)
                                        {
                                            _gameMenu.setTeamColor(data.color);
                                            _gameMenu.init(_level,data.gold);
                                        }
                                    }

                                    _status = StatusInGame;
                                }

                            }break;
                            case FuncIds::IdJoinGameReject :
                            {
                               //print a message or whatever
                            }break;
                            default : break;
                        }
                    }break;
                    case StatusInGame :
                    {
                        _gameMenu.processNetworkEvent(msg);
                        _level->processNetworkEvent(msg);
                        
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
            case Status::StatusInGame :
            {
                _gameMenu.update(deltaTime);
                _level->update(deltaTime);

                if(_gameMenu.getStatus() == GameMenu::Exit)
                {
                    _status = StatusMainMenu;
                    delete _level;
                    _level = nullptr;
                    _team = -1;

                    sf::Packet packet;
                    packet<<packet::LogOut();

                    _client.send(packet);
                }

            }break;
            case Status::StatusDisconnected :
            {
            }break;
        }

        sf::Vector2i mouse(sf::Mouse::getPosition(_window));
        _cursor.setPosition(mouse.x,mouse.y);
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
            case Status::StatusInGame :
            {
                 _level->draw(_window);
                 _gameMenu.draw(_window);
            }break;
            case Status::StatusDisconnected :
            {
            }break;
        }
         _window.draw(_cursor);

        _window.display();
    }
}
