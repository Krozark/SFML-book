#include <SFML-Book/Game.hpp>
#include <SFML-Book/Piece.hpp>
#include <SFML-Book/random.hpp>

#include <SFML/Graphics.hpp>

#include <string>
#include <cmath>

namespace book
{


Game::Game() : _window(sf::VideoMode(800, 600),"SFML Tetris"),_board()
{
    rand_init();

    //create the tertis board with default values
    _board.setPosition(10,10);
    _stats.setPosition(300,10);

    newPiece();
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


/********* private ************/

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
            else if (event.key.code == sf::Keyboard::Down)
            {
                _board.move(*_currentPiece,0,1);
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                _board.move(*_currentPiece,0,-1);
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                _board.move(*_currentPiece,-1,0);
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                _board.move(*_currentPiece,1,0);
            }
            else if (event.key.code == sf::Keyboard::Space)
            {
                _board.drop(*_currentPiece);
                newPiece();
            }
            else if (event.key.code == sf::Keyboard::S)
            {
                _board.rotateRight(*_currentPiece);
            }
            else if (event.key.code == sf::Keyboard::D)
            {
                _board.rotateLeft(*_currentPiece);
            }
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    //update stats
    if(not _board.isGameOver())
    {
        _stats.addLines(_board.clearLines(*_currentPiece));
        _nextFall += deltaTime;
        if((not _board.isFallen(*_currentPiece)) and  (_currentPiece->getTimeSinceLastMove() > sf::seconds(1.f)))
            newPiece();
        sf::Time max_time = sf::seconds(std::max(0.1,0.6-0.005*_stats.getLvl()));
        while(_nextFall > max_time)
        {
            _nextFall -= max_time;
            _board.move(*_currentPiece,0,1);
        } 
    }
    else
    {
        _stats.gameOver();
    }
}

void Game::render()
{
    //Clear screen
    _window.clear();

    if(not _board.isGameOver())
    {
        _window.draw(_board);
    }
    _window.draw(_stats);

    //Update the window
    _window.display();
}

void Game::newPiece()
{
    _currentPiece.reset(new Piece((Piece::Tetrimino_Types)random(0,Piece::Tetrimino_Types::SIZE-1),0));
    _board.spawn(*_currentPiece);
}
}
