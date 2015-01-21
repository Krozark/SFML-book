#include <SFML-utils/Map.hpp>

#include <list>
#include <iostream>

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"07 2D iso game");
    window.setFramerateLimit(65);

    sfutils::VMap* map = sfutils::createMapFromFile("./media/map.json");
    if(not map)
    {
        std::cerr<<"unable to load map"<<std::endl;
        return 0;
    }
    map->loadFromFile("./media/map2.json");

    sfutils::MapViewer viewer(window,*map);
    viewer.setSize(1600,900);

    sf::Clock clock;

    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
            else
                viewer.processEvent(event);
        }
        viewer.processEvents();

        float deltaTime = clock.restart().asSeconds();
        viewer.update(deltaTime);

        window.draw(viewer);
        
        window.display();

        window.setTitle("Example Tile ("+std::to_string(int(1/deltaTime))+")");
    }

    return 0;
};
