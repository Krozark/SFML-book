#include <SFML-Book/Game.hpp>

namespace book
{
    Game::Game(int X, int Y) : _window(sf::VideoMode(X,Y),"07 2D Iso Game")
    {
    }

    void Game::run(int minimum_frame_per_seconds)
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
