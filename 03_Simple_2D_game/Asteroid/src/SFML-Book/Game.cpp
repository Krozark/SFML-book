#include <SFML-Book/Game.hpp>

#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/random.hpp>
#include <SFML-Book/Meteor.hpp>
#include <SFML-Book/Saucer.hpp>
#include <SFML-Book/Player.hpp>

namespace book
{
    Game::Game(int X, int Y) : _window(sf::VideoMode(X,Y),"03_Asteroid"), _world(X,Y)
    {
        _txt.setFont(Configuration::fonts.get(Configuration::Fonts::Gui));
        _txt.setCharacterSize(70);
        _txt.setString("Press any Key to start");

        sf::FloatRect size = _txt.getGlobalBounds();
        _txt.setOrigin(size.width/2,size.height/2);
        _txt.setPosition(X/2,Y/2);
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
            do{
                meteor->setPosition(random(0.f,(float)_world.getX()),random(0.f,(float)_world.getY()));
            }while(_world.isCollide(*meteor));
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

            if(Configuration::isGameOver())
            {
                if (event.type == sf::Event::KeyPressed) //keyboard input
                    reset();
            }
            else
            {
                if(Configuration::player != nullptr)
                    Configuration::player->processEvent(event);
            }
        }
        if(not Configuration::isGameOver() and Configuration::player != nullptr)
            Configuration::player->processEvents();
    }

    
    void Game::update(sf::Time deltaTime)
    {

        if(not Configuration::isGameOver())
        {
            _world.update(deltaTime);
            if(Configuration::player == nullptr)
            {
                Configuration::player = new Player(_world);
                Configuration::player->setPosition(_world.getX()/2,_world.getY()/2);
                _world.add(Configuration::player);
            }
            _nextSaucer -= deltaTime;

            if(_nextSaucer < sf::Time::Zero)
            {
                Saucer::newSaucer(_world);
                _nextSaucer = sf::seconds(book::random(10.f,60.f - Configuration::level*2));
            }

            if(_world.size() <= 1)
            {
                ++Configuration::level;
                initLevel();
            }
        }
    }

    void Game::render()
    {
        //Clear screen
        _window.clear();

        //Draw
        if(Configuration::isGameOver())
        {
            _window.draw(_txt);
        }
        else
        {
            _window.draw(_world);

            Configuration::draw(_window);
        }

        //Update the window
        _window.display();
    }

    void Game::reset()
    {
        _nextSaucer = sf::seconds(book::random(5.f,6.f - Configuration::level*2));
        _world.clear();
        Configuration::player = nullptr;
        Configuration::reset();
        initLevel();
    }




}
