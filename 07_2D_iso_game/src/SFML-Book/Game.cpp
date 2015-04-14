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
        onPickup = [this](Level::Param& param){
            if(param.entity.has<CompTeam>())
            {
                CompTeam::Handle team = param.entity.component<CompTeam>();
                if(team->_team->id() == _team[_team_id]->id())
                {
                    _team[_team_id]->gui.setSelected(param.entity.id(),param.entity.getManager());
                }
            }
        };

        _team[0] = new Team(0,_window);
        _team[1] = new Team(1,_window);

        _team[0]->addEnemy(_team[1]);
        _team[1]->addEnemy(_team[0]);

        _team_id = 0;

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

            initTeam(_team[0],sf::Vector2i(10,10));
            initTeam(_team[1],sf::Vector2i(30,30));

        }catch(...)
        {
            std::cerr<<"impossible to create level "<<level<<std::endl;
            res = false;
        }
        return res;
    }

    void Game::run(int frame_per_seconds)
    {
        sf::Clock clock;
        sf::Time timeSinceLastUpdate;
        sf::Time TimePerFrame = sf::seconds(1.f/frame_per_seconds);

        while (_window.isOpen())
        {

            bool repaint = false;

            //fix time delta between frames
            sf::Time delta = clock.restart();
            timeSinceLastUpdate += delta;
            if(timeSinceLastUpdate > TimePerFrame)
            {
                processEvents();
                timeSinceLastUpdate -= TimePerFrame;
                repaint = true;
                update(TimePerFrame);
            }

            if(repaint)
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
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Return)
                _team_id = (_team_id +1) %2;
            else
            {
                bool used = false;
                if(_team[_team_id])
                    used = _team[_team_id]->gui.processEvent(event);
                if(_level and not used)
                    _level->processEvent(event);
            }
        }
        if(_team[_team_id])
            _team[_team_id]->gui.processEvents();
        if(_level)
            _level->processEvents();
    }

    
    void Game::update(sf::Time deltaTime)
    {
        if(_team[_team_id])
            _team[_team_id]->gui.update(deltaTime);
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
        if(_team[_team_id])
            _team[_team_id]->gui.draw(_window);

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
        team->addGold(10000);
    }
}
