#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc,char* argv[])
{
    //the window use for the display
    sf::RenderWindow window(sf::VideoMode(400,400),"01_Introduction");
    //set the maximum frame per second
    window.setFramerateLimit(60);

    //construct a circle
    sf::CircleShape circle(150);
    //set his color
    circle.setFillColor(sf::Color::Blue);
    //set his position
    circle.setPosition(10, 20);

    //main loop
    while (window.isOpen())
    {
        //to store the events
        sf::Event event;
        //process events
        while(window.pollEvent(event))
        {
            //Close window
            if (event.type == sf::Event::Closed)
                window.close();
            //keyboard input : Escape is press
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        //Clear screen
        window.clear();

        //draw the cirle
        window.draw(circle);

        //Update the window
        window.display();

    }

    return 0;
}
