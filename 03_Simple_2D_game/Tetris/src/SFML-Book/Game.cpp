#include <SFML-Book/Game.hpp>
#include <SFML-Book/Piece.hpp>
#include <SFML-Book/random.hpp>

#include <SFML/Graphics.hpp>

#include <string>

#define MAX_FPS 60

namespace book
{

sf::Time TimePerFrame = sf::seconds(1.f/MAX_FPS);


Game::Game() : _window(sf::VideoMode(800, 600),"SFML Tetris"),_board()
{
    rand_init();
    //limit the number of FPS
    _window.setFramerateLimit(MAX_FPS);

    //create the tertis board with default values
    _board.setPosition(10,10);
    _stats.setPosition(300,10);

    newPiece();
}

void Game::run()
{
    //main loop
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (_window.isOpen())
    {
        //Process events
        //processEvents();

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
                _board.move(*_current_piece,0,1);
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                _board.move(*_current_piece,0,-1);
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                _board.move(*_current_piece,-1,0);
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                _board.move(*_current_piece,1,0);
            }
            else if (event.key.code == sf::Keyboard::Space)
            {
                _board.drop(*_current_piece);
                newPiece();
            }
            else if (event.key.code == sf::Keyboard::A)
            {
                _board.rotateRight(*_current_piece);
            }
            else if (event.key.code == sf::Keyboard::U)
            {
                _board.rotateLeft(*_current_piece);
            }
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    //update stats
    _stats.addLines(_board.clearLines(*_current_piece));

    if((not _board.isFallen(*_current_piece)) and  (_current_piece->getTimeSinceLastMove() > sf::seconds(1.f)))
        newPiece();

}

void Game::render()
{
    //Clear screen
    _window.clear();

    //Draw
    _window.draw(_board);
    _window.draw(_stats);

    //Update the window
    _window.display();
}

void Game::newPiece()
{
    //TODO _board.isGameOver()
    _current_piece.reset(new Piece((Piece::Tetrimino_Types)random(0,Piece::Tetrimino_Types::SIZE-1),0));
    _board.spawn(*_current_piece);
}
}
