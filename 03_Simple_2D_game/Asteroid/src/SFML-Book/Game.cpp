#include <SFML-Book/Game.hpp>
#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/random.hpp>

#include <SFML-Book/Meteor.hpp>
#include <SFML-Book/Saucer.hpp>

namespace book
{
    Game::Game(int X, int Y) : _window(sf::VideoMode(X,Y),"03_Asteroid"), _world(X,Y)
    {
        _next_saucer = sf::seconds(book::random(5.f,6.f - Configuration::level*2));
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
            Meteor* meteor = new BigMeteor(_world);
            meteor->setPosition(random(0.f,(float)_world.getX()),random(0.f,(float)_world.getY()));
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

        if(Configuration::player != nullptr)
            Configuration::player->processEvents();
    }

    
    void Game::update(sf::Time deltaTime)
    {
        _world.update(deltaTime);
        if(Configuration::player == nullptr)
        {
            Configuration::player = new Player(_world);
            Configuration::player->setPosition(_world.getX()/2,_world.getY()/2);
            _world.add(Configuration::player);
        }
        _next_saucer -= deltaTime;

        if(_next_saucer < sf::Time::Zero)
        {
            Saucer::newSaucer(_world);
            _next_saucer = sf::seconds(book::random(5.f,60.f - Configuration::level*2));
        }
    }

    void Game::render()
    {
        //Clear screen
        _window.clear();

        //Draw
        _window.draw(_world);

        Configuration::draw(_window);

        //Update the window
        _window.display();
    }




}
