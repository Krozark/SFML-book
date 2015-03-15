#include <SFML-Book/Game.hpp>
#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Piece.hpp>

namespace book
{
    Game::Game(int X, int Y,int word_x,int word_y) : ActionTarget(Configuration::playerInputs), _window(sf::VideoMode(X,Y),"04_Gravitris"),_currentPiece(nullptr), _world(word_x,word_y)
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

        _currentPiece = _world.newPiece();
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

            if(not _stats.isGameOver())
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

    void Game::processEvents()
    {
        //to store the events
        sf::Event event;
        //events loop
        while(_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//Close window
                _window.close();
            else if (event.type == sf::Event::KeyPressed) //keyboard input
            {
                if (event.key.code == sf::Keyboard::Escape)
                    _window.close();
            }

            ActionTarget::processEvent(event);
        }
        ActionTarget::processEvents();
    }

    void Game::render()
    {
        _window.clear();

        if(not _stats.isGameOver())
        {
            _window.draw(_world);
        }
        _window.draw(_stats);

        _window.display();
#ifdef BOOK_DEBUG
        _world.displayDebug();
#endif
    }
}
