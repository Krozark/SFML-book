#include <SFML-Book/Game.hpp>

#define MAX_FPS 60

sf::Time TimePerFrame = sf::seconds(1.f/MAX_FPS);


namespace book
{
    Game::Game() : _window(sf::VideoMode(800, 600),"01_Introduction")
    {
        _window.setFramerateLimit(MAX_FPS);
    }

    void Game::run()
    {
        //main loop
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        while (_window.isOpen())
        {
            //Process events
            processEvents();

            //fix time delta between frames
            timeSinceLastUpdate += clock.restart();
            while (timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                processEvents();
                //do some updates
                update(TimePerFrame);
            }

            //draw stuff
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
                {
                    _window.close();
                }
            }
        }
    }

    
    void Game::update(sf::Time deltaTime)
    {
    }

    void Game::render()
    {
        //Clear screen
        _window.clear();

        //Draw
        //_window.draw(_board);

        //Update the window
        _window.display();
    }




}
