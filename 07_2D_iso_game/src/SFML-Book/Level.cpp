#include <SFML-Book/Level.hpp>

#include <stdexcept>

#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/System.hpp>

namespace book
{
    Level::FuncType Level::defaultFunc = [](Level::Param&){};

    Level::Level(sf::RenderWindow& window,const std::string& filename) : 
        onPickup(defaultFunc),
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

        _map->add(_entites_layer);

        systems.add<SysAIMain>();
        systems.add<SysAIWarrior>();
        systems.add<SysAIDefender>();
        systems.add<SysAISpawner>(*this);
        systems.add<SysAIWalker>();
        systems.add<SysAIFlyer>();
        systems.add<SysSkin>();
        systems.add<SysHp>();

    }
    Level::~Level()
    {
        entites.reset();
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
                std::list<Entity*> pick = _entites_layer->getByCoords(coord,*_map);
                for(Entity* e : pick)
                {
                    Param p(coord,*e,*_entites_layer,*_map);
                    onPickup(p);
                }

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

    void Level::draw(sf::RenderTarget& window)
    {
        _viewer.draw();
    }

    Level::Param::Param(sf::Vector2i& c,Entity& e,sfutils::Layer<sfutils::HexaIso,Entity*>& l,sfutils::VMap& m) : 
        coord(c), entity(e),layer(l),map(m)
    {
    }

    sfutils::EntityManager<Entity>& Level::entityManager()
    {
        return entites;
    }

    Entity& Level::createEntity(const sf::Vector2i& coord)
    {
        std::uint32_t id = entites.create(*_entites_layer);
        Entity& e = entites.get(id);
        e.init();
        e.setPosition(_map->mapCoordsToPixel(coord));
        return e;
    }

    sf::Vector2i Level::mapPixelToCoords(const sf::Vector2f& pos)const
    {
        return _map->mapPixelToCoords(pos);
    }

    sf::Vector2f Level::mapCoordsToPixel(const sf::Vector2i& pos)const
    {
        return _map->mapCoordsToPixel(pos);
    }
}
