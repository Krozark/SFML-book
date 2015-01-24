#include <SFML-Book/Level.hpp>

#include <iostream>
#include <stdexcept>

#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Helpers.hpp>
#include <SFML-Book/System.hpp>

namespace book
{
    Level::Level(sf::RenderWindow& window,const std::string& filename) : 
        _map(sfutils::createMapFromFile(filename)),
        _viewer(window,*_map),
        _mouse_layer(new sfutils::Layer<sfutils::HexaIso,sf::ConvexShape>("ConvexShape",1)),
        _entites_layer(new sfutils::Layer<sfutils::HexaIso,Entity*>("Entity",2))
    {
        if(_map == nullptr)
        {
            //do some error
            throw std::runtime_error("Impossible to load file " + filename);
        }

        {
            _mouse_light = _mouse_layer->add(_map->getShape());
            _mouse_light->setFillColor(sf::Color(255,255,255,64));
            _map->add(_mouse_layer);
        }

        {
            for(int i=0;i<4;++i)
            {
                uint32_t id = makeMain(entites,*_entites_layer,nullptr);
                Entity* e = entites.getPtr(id);
                e->setPosition(_map->mapCoordsToPixel(i,i));

            }
            _map->add(_entites_layer);
        }

        systems.add<SysSkin>();

    }
    Level::~Level()
    {
        delete _map;
    }

    void Level::update(sf::Time deltaTime)
    {
        _viewer.update(deltaTime.asSeconds());
        systems.updateAll(deltaTime);
    }

    void Level::processEvents()
    {
        _viewer.processEvents();
    }

    bool Level::processEvent(sf::Event& event)
    {
        bool res = _viewer.processEvent(event);

        if(not res)
        {
            if(event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Button::Left)
            {
                sf::Vector2i coord = _viewer.mapPixelToCoords(event.mouseButton.x,event.mouseButton.y);
                std::cout<<"pickup on "<<coord.x<<" "<<coord.y<<std::endl;
            }
            else if(event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i coord = _viewer.mapPixelToCoords(event.mouseMove.x,event.mouseMove.y);
                sf::Vector2f pos = _viewer.mapCoordsToPixel(coord.x,coord.y);
                _mouse_light->setPosition(pos);
            }
        }
        return res;
    }

    void Level::draw(sf::RenderWindow& window)
    {
        _viewer.draw();
    }
}
