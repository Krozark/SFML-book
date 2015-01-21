#include <SFML-Book/Game.hpp>
#include <SFML-Book/Level.hpp>

namespace book
{
    Game::Game(int X, int Y) : _window(sf::VideoMode(X,Y),"07 2D Iso Game"), _level(nullptr)
    {
        _window.setFramerateLimit(65);
    }

    Game::~Game()
    {
        delete _level;
    }

    bool Game::load(const std::string& level)
    {
        delete _level;
        _level = new Level(_window,level);
        return _level != nullptr;
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
            if (event.type == sf::Event::Closed)
                _window.close();
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
                _window.close();
            else if(_level)
                _level->processEvent(event);
        }
        if(_level)
            _level->processEvents();
    }

    
    void Game::update(sf::Time deltaTime)
    {
        if(_level)
        {
            _level->update(deltaTime);
        }
    }

    void Game::render()
    {
        _window.clear();

        if(_level)
        {
            _level->draw(_window);
        }

        _window.display();
    }
}
