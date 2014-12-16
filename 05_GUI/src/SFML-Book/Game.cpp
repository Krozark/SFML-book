#include <SFML-Book/Game.hpp>
#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Piece.hpp>

namespace book
{
    Game::Game(int X, int Y,int word_x,int word_y) : ActionTarget(Configuration::player_inputs), _window(sf::VideoMode(X,Y),"05_GUi"),_current_piece(nullptr), _world(word_x,word_y), _mainMenu(_window),_pauseMenu(_window),_status(Status::StatusMainMenu)
    {
        bind(Configuration::PlayerInputs::HardDrop,[this](const sf::Event&){        
             _current_piece = _world.newPiece();
             timeSinceLastFall = sf::Time::Zero;
        });

        bind(Configuration::PlayerInputs::TurnLeft,[this](const sf::Event&){
             _rotate_direction-=1;
        });
        bind(Configuration::PlayerInputs::TurnRight,[this](const sf::Event&){        
             _rotate_direction+=1;
        });

        bind(Configuration::PlayerInputs::MoveLeft,[this](const sf::Event&){        
             _move_direction-=1;
        });

        bind(Configuration::PlayerInputs::MoveRight,[this](const sf::Event&){        
             _move_direction+=1;
        });


        _stats.setPosition(BOOK_BOX_SIZE*(word_x+3),BOOK_BOX_SIZE);

        initGui();

    }

    void Game::run(int minimum_frame_per_seconds, int physics_frame_per_seconds)
    {
        sf::Clock clock;
        const sf::Time timePerFrame = sf::seconds(1.f/minimum_frame_per_seconds);
        const sf::Time timePerFramePhysics = sf::seconds(1.f/physics_frame_per_seconds);

        while (_window.isOpen())
        {
            sf::Time time = clock.restart();

            processEvents();

            if(_status == StatusGame and not _stats.isGameOver())
            {
                update_physics(time,timePerFramePhysics);
                update(time,timePerFrame);
            }

            render();
        }
    }
    void Game::update(const sf::Time& deltaTime,const sf::Time& timePerFrame)
    {
        static sf::Time timeSinceLastUpdate = sf::Time::Zero;

        timeSinceLastUpdate+=deltaTime;
        timeSinceLastFall+=deltaTime;

        if(timeSinceLastUpdate > timePerFrame)
        {
            if(_current_piece != nullptr)
            {
                _current_piece->rotate(_rotate_direction*3000);
                _current_piece->moveX(_move_direction*5000);

                bool new_piece;
                {
                    int old_level =_stats.getLevel();
                    _stats.addLines(_world.clearLines(new_piece,*_current_piece));
                    if(_stats.getLevel() != old_level)
                        _world.add(Configuration::Sounds::LevelUp);
                }

                if(new_piece or timeSinceLastFall.asSeconds() > std::max(1.0,10-_stats.getLevel()*0.2))
                {
                    _current_piece = _world.newPiece();
                    timeSinceLastFall = sf::Time::Zero;
                }
            }
            _world.update(timePerFrame);
            _stats.setGameOver(_world.isGameOver());
            timeSinceLastUpdate = sf::Time::Zero;
        }
        _rotate_direction=0;
        _move_direction=0;
    }

    void Game::update_physics(const sf::Time& deltaTime,const sf::Time& timePerFrame)
    {
        static sf::Time timeSinceLastUpdate = sf::Time::Zero;

        timeSinceLastUpdate+=deltaTime;

        _world.updateGravity(_stats.getLevel());

        while (timeSinceLastUpdate > timePerFrame)
        {
            _world.update_physics(timePerFrame);
            timeSinceLastUpdate -= timePerFrame;
        }
    }

    void Game::initGui()
    {
        //_mainMenu
        {
            book::gui::VLayout* layout = new book::gui::VLayout;
            layout->setSpace(25);

            book::gui::TextButton* newGame = new book::gui::TextButton("New Game");
            newGame->on_click = [this](const sf::Event&, book::gui::Button& button){
                initGame();
                _status = Status::StatusGame;
            };
            layout->add(newGame);

            book::gui::TextButton* configuration = new book::gui::TextButton("Configuration");
            configuration->on_click = [this](const sf::Event&, book::gui::Button& button){
                _status = Status::StatusConfiguration;
            };
            layout->add(configuration);

            book::gui::TextButton* exit = new book::gui::TextButton("Exit");
            exit->on_click = [this](const sf::Event&, book::gui::Button& button){
                _window.close();
            };
            layout->add(exit);

            _mainMenu.setLayout(layout);

            _mainMenu.bind(Configuration::GuiInputs::Escape,[this](const sf::Event& event){
                               this->_window.close();
                           });
        }
        //_pauseMenu
        {
            book::gui::VLayout* layout = new book::gui::VLayout;
            layout->setSpace(50);

            book::gui::Label* pause = new book::gui::Label("Pause");
            pause->setCharacterSize(70);
            layout->add(pause);

            book::gui::TextButton* exit = new book::gui::TextButton("Exit");
            exit->on_click = [this](const sf::Event&, book::gui::Button& button){
                _status = StatusMainMenu;
            };
            layout->add(exit);

            _pauseMenu.setLayout(layout);

            _pauseMenu.bind(Configuration::GuiInputs::Escape,[this](const sf::Event& event){
                _status = StatusGame;
            });
        }
    }

    void Game::initGame()
    {
        timeSinceLastFall = sf::Time::Zero;

        _stats.reset();
        _world.reset();

        _current_piece = _world.newPiece();
    }

    void Game::processEvents()
    {
        //to store the events
        sf::Event event;
        //events loop
        while(_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//Close window
                _window.close();
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape and _status == Status::StatusGame)
            {
                _status = StatusPaused;
            }
            else
            {
                switch(_status)
                {
                    case StatusMainMenu:
                    {
                        _mainMenu.processEvent(event);
                    }break;
                    case StatusGame :
                    {
                        ActionTarget::processEvent(event);
                    }break;
                    case StatusPaused :
                    {
                        _pauseMenu.processEvent(event);
                    }break;
                    default : break;
                }
            }
        }

        switch(_status)
        {
            case StatusMainMenu:
            {
                _mainMenu.processEvents();
            }break;
            case StatusGame :
            {
                ActionTarget::processEvents();
            }break;
            case StatusPaused :
            {
                _pauseMenu.processEvents();
            }break;
            default : break;
        }
    }

    void Game::render()
    {
        _window.clear();

        switch(_status)
        {
            case StatusMainMenu:
            {
                _window.draw(_mainMenu);
            }break;
            case StatusGame :
            {
                if(not _stats.isGameOver())
                    _window.draw(_world);
                _window.draw(_stats);

#ifdef BOOK_DEBUG
                _world.displayDebug();
#endif
            }break;
            case StatusPaused :
            {
                if(not _stats.isGameOver())
                    _window.draw(_world);
                _window.draw(_pauseMenu);
            }break;
            default : break;
        }

        _window.display();

    }
}
