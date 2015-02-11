#include <SFML-Book/client/Level.hpp>

#include <stdexcept>
#include <ctime>

//#include <SFML-Book/common/System.hpp>
//#include <SFML-Book/common/Component.hpp>


namespace book
{
    //Level::FuncType Level::defaultFunc = [](Level::Param&){};

    Level::Level(sf::RenderWindow& window,std::istream& stream) : 
        //onPickup(defaultFunc),
        _map(sfutils::VMap::createMapFromStream(stream)),
        _viewer(window,*_map,Configuration::map_inputs),
        _mouse_layer(new sfutils::Layer<sf::ConvexShape>("ConvexShape",1))
        //_entities_layer(new sfutils::Layer<Entity*>("Entity",2))
    {
        //Map
        if(_map == nullptr)
        {
            //do some error
            throw std::runtime_error("Impossible to load file map");
        }


        {
            _mouse_light = _mouse_layer->add(_map->getShape());
            _mouse_light->setFillColor(sf::Color(255,255,255,64));
            _map->add(_mouse_layer);
        }
        //_map->add(_entities_layer);

        //Viewer
        _viewer.bind(Configuration::MapInputs::TakeScreen,[&window](const sf::Event& event){
             sf::Image screen = window.capture();

             time_t rawtime;
             struct tm * timeinfo;
             char buffer[128];

             std::time(&rawtime);
             timeinfo = std::localtime(&rawtime);
             std::strftime (buffer,128,"screen/%F_%T.png",timeinfo);
             screen.saveToFile(std::string(buffer));
         });
        
        //ES
        /*systems.add<SysAIMain>();
        systems.add<SysAIWarrior>(*this);
        systems.add<SysAIDefender>(*this);
        systems.add<SysAISpawner>(*this);
        systems.add<SysAIWalker>(*this);
        systems.add<SysAIFlyer>(*this);
        systems.add<SysSkin>();
        systems.add<SysHp>(*this);
        systems.add<SysEffect>(*this);*/


    }
    Level::~Level()
    {
        //entites.reset();
        delete _map;
    }

    void Level::update(sf::Time deltaTime)
    {
        _viewer.update(deltaTime.asSeconds());
        //Application::update(deltaTime);
        //_entities_layer->sort();

        sf::Vector2f pos = _viewer.getPosition();

        sf::Listener::setPosition(pos.x,pos.x,_viewer.getZoom());

        _sounds.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {
              return sound->getStatus() != sf::SoundSource::Status::Playing;
          });

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
                sf::Vector2i coord = _viewer.mapScreenToCoords(event.mouseButton.x,event.mouseButton.y);
                /*std::list<Entity*> pick = getByCoords(coord);
                for(Entity* e : pick)
                {
                    Param p(coord,*e,*_entities_layer,*_map);
                    onPickup(p);
                }*/

            }
            else if(event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i coord = _viewer.mapScreenToCoords(event.mouseMove.x,event.mouseMove.y);
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

    /*Level::Param::Param(sf::Vector2i& c,Entity& e,sfutils::Layer<Entity*>& l,sfutils::VMap& m) : 
        coord(c), entity(e),layer(l),map(m)
    {
    }

    sfutils::EntityManager<Entity>& Level::entityManager()
    {
        return entites;
    }*/

    sfutils::Layer<sf::ConvexShape>& Level::getHighlightLayer()const
    {
        return *_mouse_layer;
    }

    const sf::ConvexShape Level::getShape()const
    {
        return _map->getShape();
    }

    /*Entity& Level::createEntity(const sf::Vector2i& coord)
    {
        std::uint32_t id = entites.create();
        Entity& e = entites.get(id);

        e.add<CompSkin>();
        e.setPosition(_map->mapCoordsToPixel(coord));

        _entities_layer->add(&e);
        _byCoords[coord].emplace_back(&e);

        return e;
    }

    void Level::destroyEntity(std::uint32_t id)
    {
        const sf::Vector2i coord = mapPixelToCoords(entites.getComponent<CompSkin>(id)->_sprite.getPosition());
        Entity& e = entites.get(id);

        _entities_layer->remove(&e,false);
        _byCoords[coord].remove(&e);
        e.remove();
    }

    void Level::destroyEntity(Entity& e)
    {
        const sf::Vector2i coord = mapPixelToCoords(entites.getComponent<CompSkin>(e.id())->_sprite.getPosition());

        _entities_layer->remove(&e,false);

        _byCoords[coord].remove(&e);
        e.remove();
    }

    void Level::setPosition(Entity& e,const sf::Vector2i& old,const sf::Vector2i& n)
    {
        if(n != old)
        {
            _byCoords[old].remove(&e);
            _byCoords[n].emplace_back(&e);
        }
    }*/
    
    void Level::createSound(Configuration::Sounds sound_id,const sf::Vector2i& coord)
    {
        sf::Vector2f pos = _map->mapCoordsToPixel(coord);
        createSound(sound_id,pos);
    }

    void Level::createSound(Configuration::Sounds sound_id,const sf::Vector2f& pos)
    {
        std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds.get(sound_id)));
        sound->setPosition(pos.x,pos.y,0);
        sound->setRelativeToListener(true);
        sound->setVolume(100);
        sound->setAttenuation(1);

        sound->play();
        _sounds.emplace_back(std::move(sound));
    }


   /* sf::Vector2i Level::mapPixelToCoords(const sf::Vector2f& pos)const
    {
        return _map->mapPixelToCoords(pos);
    }

    sf::Vector2f Level::mapCoordsToPixel(const sf::Vector2i& pos)const
    {
        return _map->mapCoordsToPixel(pos);
    }

    sf::Vector2i Level::mapCoordsToScreen(const sf::Vector2i& pos)const
    {
        return _viewer.mapCoordsToScreen(pos);
    }

    sf::Vector2i Level::mapScreenToCoords(const sf::Vector2i& pos)const
    {
        return _viewer.mapScreenToCoords(pos);
    }

    std::list<Entity*> Level::getByCoords(const sf::Vector2i& coord)
    {
        return _byCoords[coord];
    }

    //TODO A* or dijtra
    std::list<sf::Vector2i> Level::getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const
    {
        return _map->getPath(origin,dest);
    }

    sf::Vector2i Level::getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const
    {
        return _map->getPath1(origin,dest);
    }

    int Level::getDistance(const sf::Vector2i& origin,const sf::Vector2i& dest)const
    {
        return _map->getDistance(origin,dest);
    }*/

    sf::Vector2i Level::getMinCoord()const
    {
        return sf::Vector2i(0,0);
    }

    sf::Vector2i Level::getMaxCoord()const
    {
        return sf::Vector2i(99,99);
    }
}
