#include <SFML-Book/Game.hpp>

namespace book
{
    Game::Game(int X, int Y,int word_x,int word_y) : _window(sf::VideoMode(X,Y),"04_Gravitris"), _world(word_x,word_y)
    {
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

            _world.processEvent(event);
        }
        _world.processEvents();
    }

    void Game::render()
    {
        _window.clear();

        _window.draw(_world);

        _window.display();
    }
}
