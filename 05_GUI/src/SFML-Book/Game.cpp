#include <SFML-Book/Game.hpp>
#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Piece.hpp>

#include <sstream>

namespace book
{
    Game::Game(int X, int Y,int word_x,int word_y) : ActionTarget(Configuration::playerInputs), _window(sf::VideoMode(X,Y),"05_GUI"),_currentPiece(nullptr), _world(word_x,word_y), _mainMenu(_window),_configurationMenu(_window),_pauseMenu(_window),_status(Status::StatusMainMenu)
    {
        bind(Configuration::PlayerInputs::HardDrop,[this](const sf::Event&){        
             _currentPiece = _world.newPiece();
             timeSinceLastFall = sf::Time::Zero;
        });

        bind(Configuration::PlayerInputs::TurnLeft,[this](const sf::Event&){
             _rotateDirection-=1;
        });
        bind(Configuration::PlayerInputs::TurnRight,[this](const sf::Event&){        
             _rotateDirection+=1;
        });

        bind(Configuration::PlayerInputs::MoveLeft,[this](const sf::Event&){        
             _moveDirection-=1;
        });

        bind(Configuration::PlayerInputs::MoveRight,[this](const sf::Event&){        
             _moveDirection+=1;
        });


        _stats.setPosition(BOOK_BOX_SIZE*(word_x+3),BOOK_BOX_SIZE);

        initGui();

    }

    void Game::run(int minimum_framePer_seconds, int physics_framePer_seconds)
    {
        sf::Clock clock;
        const sf::Time timePerFrame = sf::seconds(1.f/minimum_framePer_seconds);
        const sf::Time timePerFramePhysics = sf::seconds(1.f/physics_framePer_seconds);

        while (_window.isOpen())
        {
            sf::Time time = clock.restart();

            processEvents();

            if(_status == StatusGame and not _stats.isGameOver())
            {
                updatePhysics(time,timePerFramePhysics);
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
            if(_currentPiece != nullptr)
            {
                _currentPiece->rotate(_rotateDirection*3000);
                _currentPiece->moveX(_moveDirection*5000);

                bool new_piece;
                {
                    int old_level =_stats.getLevel();
                    _stats.addLines(_world.clearLines(new_piece,*_currentPiece));
                    if(_stats.getLevel() != old_level)
                        _world.add(Configuration::Sounds::LevelUp);
                }

                if(new_piece or timeSinceLastFall.asSeconds() > std::max(1.0,10-_stats.getLevel()*0.2))
                {
                    _currentPiece = _world.newPiece();
                    timeSinceLastFall = sf::Time::Zero;
                }
            }
            _world.update(timePerFrame);
            _stats.setGameOver(_world.isGameOver());
            timeSinceLastUpdate = sf::Time::Zero;
        }
        _rotateDirection=0;
        _moveDirection=0;
    }

    void Game::updatePhysics(const sf::Time& deltaTime,const sf::Time& timePerFrame)
    {
        static sf::Time timeSinceLastUpdate = sf::Time::Zero;

        timeSinceLastUpdate+=deltaTime;

        _world.updateGravity(_stats.getLevel());

        while (timeSinceLastUpdate > timePerFrame)
        {
            _world.updatePhysics(timePerFrame);
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
            newGame->onClick = [this](const sf::Event&, book::gui::Button& button){
                initGame();
                _status = Status::StatusGame;
            };
            layout->add(newGame);

            book::gui::TextButton* configuration = new book::gui::TextButton("Configuration");
            configuration->onClick = [this](const sf::Event&, book::gui::Button& button){
                _status = Status::StatusConfiguration;
            };
            layout->add(configuration);

            book::gui::TextButton* exit = new book::gui::TextButton("Exit");
            exit->onClick = [this](const sf::Event&, book::gui::Button& button){
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
            exit->onClick = [this](const sf::Event&, book::gui::Button& button){
                _status = StatusMainMenu;
            };
            layout->add(exit);

            _pauseMenu.setLayout(layout);

            _pauseMenu.bind(Configuration::GuiInputs::Escape,[this](const sf::Event& event){
                _status = StatusGame;
            });
        }
        
        //configuration
        {
            auto title = sfg::Label::Create("Enter your starting level");
            auto level = sfg::Entry::Create();
            auto error = sfg::Label::Create();
            auto button = sfg::Button::Create( "Ok" );
            button->GetSignal( sfg::Button::OnLeftClick ).Connect(
              [level,error,this](){
                int lvl = 0;
	            std::stringstream sstr(static_cast<std::string>(level->GetText()));
	            sstr >> lvl;
                if(lvl < 1 or lvl > 100)
                    error->SetText("Enter a number from 1 to 100.");
                else
                {
                    error->SetText("");
                    initGame();
                    _stats.setLevel(lvl); 
                    _status = Status::StatusGame;
                }
              }
            );

            auto table = sfg::Table::Create();
            table->SetRowSpacings(10);

            table->Attach(title,sf::Rect<sf::Uint32>(0,0,1,1));
            table->Attach(level,sf::Rect<sf::Uint32>(0,1,1,1));
            table->Attach(button,sf::Rect<sf::Uint32>(0,2,1,1));
            table->Attach(error,sf::Rect<sf::Uint32>(0,3,1,1));

            table->SetAllocation(sf::FloatRect((_window.getSize().x-300)/2,
                                                (_window.getSize().y-200)/2,
                                                300,200));
            _sfgDesktop.Add(table);

            _configurationMenu.bind(Configuration::GuiInputs::Escape,[this](const sf::Event& event){
                _status = StatusMainMenu;
            });
        }
    }

    void Game::initGame()
    {
        timeSinceLastFall = sf::Time::Zero;

        _stats.reset();
        _world.reset();

        _currentPiece = _world.newPiece();
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
                    case StatusConfiguration :
                    {
                        _configurationMenu.processEvent(event);
                        _sfgDesktop.HandleEvent(event);
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
            case StatusConfiguration :
            {
                _configurationMenu.processEvents();
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
            case StatusConfiguration:
            {
                _sfgDesktop.Update(0.0);
                _sfgui.Display(_window);
                _window.draw(_configurationMenu);
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
