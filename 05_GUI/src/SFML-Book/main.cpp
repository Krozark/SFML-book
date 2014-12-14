#include <SFML-Book/Game.hpp>
#include <SFML-Book/Configuration.hpp>

#include <SFML-Book/gui/Gui.hpp>

#include <iostream>

int main(int argc,char* argv[])
{
    book::Configuration::initialize();

    /*book::Game game(600,900,10,20);
    game.run(30,60);*/

    sf::RenderWindow window(sf::VideoMode(800,600),"04_Gravitris");

    book::gui::VLayout layout;
    book::gui::Button button("Test");
    button.on_click = [](const sf::Event&, book::gui::Button& button){
        std::cout<<"b1"<<std::endl;
    };

    layout.add(&button);

    book::gui::Frame frame(window);
    frame.setLayout(&layout);

    while(window.isOpen())
    {
        window.clear();
        frame.draw();
        frame.processEvents();
        sf::sleep(sf::seconds(0.01));
        window.display();
    }
    return 0;
}
