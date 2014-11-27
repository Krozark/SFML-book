#include <SFML-Book/Game.hpp>
#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Piece.hpp>

namespace book
{
    Game::Game(int X, int Y,int word_x,int word_y) : ActionTarget(Configuration::player_inputs), _window(sf::VideoMode(X,Y),"04_Gravitris"),_current_piece(nullptr), _world(word_x,word_y)
    {
        bind(Configuration::PlayerInputs::HardDrop,[this](const sf::Event&){        
             _current_piece = _world.newPiece();
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

            update_physics(time,timePerFramePhysics);
            update(time,timePerFrame);

            render();
        }
    }
    void Game::update(const sf::Time& deltaTime,const sf::Time& timePerFrame)
    {
        static sf::Time timeSinceLastUpdate = sf::Time::Zero;

        timeSinceLastUpdate+=deltaTime;

        if(timeSinceLastUpdate > timePerFrame)
        {
            if(_current_piece != nullptr)
            {
                _current_piece->rotate(_rotate_direction*3000);
                _current_piece->moveX(_move_direction*5000);
                bool new_piece;
                _stats.addLines(_world.clearLines(new_piece,*_current_piece));
                if(new_piece)
                    _current_piece = _world.newPiece();
            }
            _world.update(timePerFrame);
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
