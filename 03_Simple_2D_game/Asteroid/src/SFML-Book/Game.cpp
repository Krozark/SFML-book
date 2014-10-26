#include <SFML-Book/Game.hpp>
#include <SFML-Book/Configuration.hpp>

namespace book
{
    Game::Game(int X, int Y) : _window(sf::VideoMode(X,Y),"03_Asteroid"), _world(X,Y)
    {
        _world.add(Configuration::player);
    }

    void Game::run(int minimum_frame_per_seconds)
    {
        sf::Clock clock;
        sf::Time timeSinceLastUpdate;
        sf::Time TimePerFrame = sf::seconds(1.f/minimum_frame_per_seconds);

        initLevel();

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

    void Game::initLevel()
    {
        Configuration::player->setPosition(100,100);

        int nb_meteors;
        switch(Configuration::level)
        {
            case 1 : nb_meteors = 4;break;
            case 2 : nb_meteors = 5;break;
            case 3 : nb_meteors = 7;break;
            case 4 : nb_meteors = 9;break;
            default : nb_meteors = 11;break;
        }
        for(int i = 0; i<nb_meteors;++i)
        {
            Meteor* meteor = BigMeteor;
            meteor.setPosition(random(0.f,_x),random(0.f,_y));
            _world.add(meteor);
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

        Configuration::player->processEvents();
    }

    
    void Game::update(sf::Time deltaTime)
    {
        _world.update(deltaTime);
    }

    void Game::render()
    {
        //Clear screen
        _window.clear();

        //Draw
        _window.draw(_world);

        //Update the window
        _window.display();
    }




}
