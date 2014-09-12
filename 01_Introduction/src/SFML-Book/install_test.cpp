#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600),"01_Test_install"); //< the window use for the display
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        //to store the events
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//Close window
                window.close();
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)//keyboard input
                    window.close();
        }

        //Clear screen
        window.clear();

        //Update the window
        window.display();

    }


    return 0;
}
