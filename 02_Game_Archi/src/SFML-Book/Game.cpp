#include <SFML-Book/Game.hpp>

namespace book
{
    Game::Game() : _window(sf::VideoMode(800, 600),"02_Game_Archi")
    {
        _player.setPosition(100,100);
    }

    void Game::runWithFixedTimeSteps(int frame_per_seconds)
    {
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        sf::Time TimePerFrame = sf::seconds(1.f/frame_per_seconds);

        while (_window.isOpen())
        {
            processEvents();

            bool repaint = false;

            //fix time delta between frames
            timeSinceLastUpdate += clock.restart();
            while (timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                repaint = true;
                update(TimePerFrame);
            }
            
            if(repaint)
                render();
        }
    }

    void Game::runWithVariableTimeSteps()
    {
        sf::Clock clock;

        while (_window.isOpen())
        {
            processEvents();
            update(clock.restart());
            render();
        }
    }

    void Game::runWithMinimumTimeSteps(int minimum_frame_per_seconds)
    {
        sf::Clock clock;
        sf::Time timeSinceLastUpdate;
        sf::Time TimePerFrame = sf::seconds(1.f/minimum_frame_per_seconds);

        while (_window.isOpen())
        {
            processEvents();

            timeSinceLastUpdate = clock.restart();
            while (timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                update(TimePerFrame);
            }

            update(timeSinceLastUpdate);
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
        }

        _player.processEvents();
    }

    
    void Game::update(sf::Time deltaTime)
    {
        _player.update(deltaTime);
    }

    void Game::render()
    {
        //Clear screen
        _window.clear();

        //Draw
        _window.draw(_player);

        //Update the window
        _window.display();
    }




}
