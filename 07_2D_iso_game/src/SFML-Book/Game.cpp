#include <SFML-Book/Game.hpp>

#include <SFML-Book/Helpers.hpp>
#include <SFML-Book/Component.hpp>
#include <SFML-Book/Configuration.hpp>

namespace book
{
    Game::Game(int X, int Y) : 
        _window(sf::VideoMode(X,Y),"07 2D Iso Game"),
        _cursor(Configuration::textures.get(Configuration::TexCursor)),
        _level(nullptr)
    {
        _window.setFramerateLimit(65);

        onPickup = [this](Level::Param& param){
            if(param.entity.has<CompTeam>())
            {
                CompTeam::Handle team = param.entity.component<CompTeam>();
                if(team->_team->id() == _myTeam->id())
                {
                    _myTeam->gui.setSelected(param.entity.id(),param.entity.getManager());
                }
            }
        };

        _myTeam = new Team(0,_window);
        _team2 = new Team(1,_window);

        _myTeam->addEnemy(_team2);
        _team2->addEnemy(_myTeam);

        _window.setMouseCursorVisible(false);

    }

    Game::~Game()
    {
        delete _level;
    }

    bool Game::load(const std::string& level)
    {
        bool res = true;
        try{
            delete _level;
            _level = new Level(_window,level);
            _level->onPickup = onPickup;

            initTeam(_myTeam,sf::Vector2i(10,10));
            initTeam(_team2,sf::Vector2i(30,30));

        }catch(...)
        {
            std::cerr<<"impossible to create level "<<level<<std::endl;
            res = false;
        }
        return res;
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
            else
            {
                bool used = false;
                if(_myTeam)
                    used = _myTeam->gui.processEvent(event);
                if(_level and not used)
                    used = _level->processEvent(event);
            }
        }
        if(_myTeam)
            _myTeam->gui.processEvents();
        if(_level)
            _level->processEvents();
    }

    
    void Game::update(sf::Time deltaTime)
    {
        if(_myTeam)
            _myTeam->gui.update(deltaTime);
        if(_level)
            _level->update(deltaTime);

        sf::Vector2i mouse(sf::Mouse::getPosition(_window));
        _cursor.setPosition(mouse.x,mouse.y);
    }

    void Game::render()
    {
        _window.clear();

        if(_level)
            _level->draw(_window);
        if(_myTeam)
            _myTeam->gui.draw(_window);

        _window.draw(_cursor);

        _window.display();
    }

    void Game::initTeam(Team* team,const sf::Vector2i& pos)
    {
        team->gui.setLevel(_level);
        makeAsMain(_level->createEntity(pos),team,*_level);
        makeAsWormEgg(_level->createEntity(pos+sf::Vector2i(-2,-2)),team,*_level);
        makeAsWormEgg(_level->createEntity(pos+sf::Vector2i(2,2)),team,*_level);
        makeAsWormEgg(_level->createEntity(pos+sf::Vector2i(-2,2)),team,*_level);
        makeAsWormEgg(_level->createEntity(pos+sf::Vector2i(2,-2)),team,*_level);
    }
}
