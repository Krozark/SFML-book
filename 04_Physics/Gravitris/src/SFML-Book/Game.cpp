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
             if(_current_piece)
                _current_piece->rotate(-90);
        });
        bind(Configuration::PlayerInputs::TurnRight,[this](const sf::Event&){        
             if(_current_piece)
                 _current_piece->rotate(90);
        });

        bind(Configuration::PlayerInputs::MoveLeft,[this](const sf::Event&){        
             if(_current_piece)
                 _current_piece->moveX(-1);
        });

        bind(Configuration::PlayerInputs::MoveRight,[this](const sf::Event&){        
             if(_current_piece)
                 _current_piece->moveX(1);
        });
    }

    void Game::run(int minimum_frame_per_seconds, int physics_frame_per_seconds)
    {
        sf::Clock clock;
        sf::Time timeSinceLastUpdate;
        const sf::Time TimePerFrame = sf::seconds(1.f/minimum_frame_per_seconds);

        sf::Time timeSinceLastUpdatePhysics;
        const sf::Time TimePerFramePhysics = sf::seconds(1.f/physics_frame_per_seconds);

        while (_window.isOpen())
        {

            sf::Time time = clock.restart();
            timeSinceLastUpdatePhysics += time;
            timeSinceLastUpdate += time;

            while (timeSinceLastUpdatePhysics > TimePerFramePhysics)
            {
                _world.update_physics(TimePerFramePhysics);
                timeSinceLastUpdatePhysics -= TimePerFramePhysics;
            }

            processEvents();
            if(timeSinceLastUpdate > TimePerFrame)
            {
                _world.update(TimePerFrame);
                timeSinceLastUpdate = sf::Time::Zero;
            }

            render();
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

        _window.draw(_world);

        _window.display();
#ifdef BOOK_DEBUG
        _world.displayDebug();
#endif
    }
}
