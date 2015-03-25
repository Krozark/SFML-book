#include <SFML-utils/Map.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"Example Tile");
    window.setFramerateLimit(65);

    sfutils::VMap* map = sfutils::VMap::createMapFromFile("./map.json");
    map->loadFromFile("./map2.json");

    sfutils::MapViewer viewer(window,*map);

    sfutils::Layer<sf::ConvexShape>* mouse_layer = new sfutils::Layer<sf::ConvexShape>("ConvexShape",1);

    sf::ConvexShape* mouse_light = mouse_layer->add(map->getShape());
    mouse_light->setFillColor(sf::Color(255,255,255,64));
    map->add(mouse_layer);



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
            else if(not viewer.processEvent(event))
            {
                if(event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i coord = viewer.mapScreenToCoords(event.mouseButton.x,event.mouseButton.y);
                    std::cout<<coord.x<<" "<<coord.y<<std::endl;
                }
                else if(event.type == sf::Event::MouseMoved)
                {
                    sf::Vector2i coord = viewer.mapScreenToCoords(event.mouseMove.x,event.mouseMove.y);
                    sf::Vector2f pos = viewer.mapCoordsToPixel(coord.x,coord.y);
                    mouse_light->setPosition(pos);
                }
            }
        }

        viewer.processEvents();

        float deltaTime = clock.restart().asSeconds();

        viewer.update(deltaTime);
        window.setTitle("Example Tile ("+std::to_string(int(1/deltaTime))+")");


        viewer.draw();
        
        window.display();
    }


    return 0;
};
