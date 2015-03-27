#include <SFML-Book/client/Level.hpp>

#include <stdexcept>
#include <ctime>
#include <sstream>

#include <SFML-Book/client/System.hpp>
#include <SFML-Book/client/Component.hpp>
#include <utils/json/Driver.hpp>


namespace book
{
    Level::FuncType Level::defaultFunc = [](unsigned int id,sf::Vector2i coord){};

    Level::Level(sf::RenderWindow& window,int team,std::istream& stream,const std::string& data) : 
        onPickup(defaultFunc),
        _map(sfutils::VMap::createMapFromStream(stream)),
        _viewer(window,*_map,Configuration::mapInputs),
        _mouseLayer(new sfutils::Layer<sf::ConvexShape>("ConvexShape",1)),
        _entitiesLayer(new sfutils::Layer<MapComponent*>("Entity",2))
    {
        //Map
        if(_map == nullptr)
        {
            //do some error
            throw std::runtime_error("Impossible to load file map");
        }


        {
            std::stringstream ss;
            ss<<data;

            utils::json::Value* rootPtr = utils::json::Driver::parse(ss);

            utils::json::Object& root = *rootPtr;
            const utils::json::Object& size = root["size"];
            const utils::json::Object& min = size["min"];
            const utils::json::Object& max = size["max"];

            _minCoord.x = min["x"].as_int();
            _minCoord.y = min["y"].as_int();

            _maxCoord.x = max["x"].as_int();
            _maxCoord.y = max["y"].as_int();

            const utils::json::Object& players = root["players"];
            const utils::json::Array& spawn = players["spawn"];

            int i = 0;
            for(const utils::json::Object& value : spawn)
            {
                if(i == team)
                {
                    sf::Vector2i initial;
                    initial.x = value["x"].as_int();
                    initial.y = value["y"].as_int();
                    _viewer.setPosition(_map->mapCoordsToPixel(initial));
                    break;
                }
                ++i;
            }
        }


        {
            _mouse_light = _mouseLayer->add(_map->getShape());
            _mouse_light->setFillColor(sf::Color(255,255,255,64));
            _map->add(_mouseLayer);
        }
        _map->add(_entitiesLayer);

        //Viewer
        _viewer.bind(Configuration::MapInputs::TakeScreen,[&window](const sf::Event& event){
             sf::Image screen = window.capture();

             time_t rawtime;
             struct tm * timeinfo;
             char buffer[128];

             std::time(&rawtime);
             timeinfo = std::localtime(&rawtime);
             std::strftime (buffer,128,"screen/%F_%H-%M-%S.png",timeinfo);
             screen.saveToFile(std::string(buffer));
         });
        
        //ES
        systems.add<SysSkin>();
        systems.add<SysHp>();

    }

    Level::~Level()
    {
        //entities.reset();
        for(Effect* effect : _effects)
            delete effect;

        delete _map;
    }

    void Level::update(sf::Time deltaTime)
    {
        Application::update(deltaTime);
        _entitiesLayer->sort();

        sf::Vector2f pos = _viewer.getPosition();
        sf::Listener::setPosition(pos.x,pos.y,0);
        _viewer.update(deltaTime.asSeconds());

        auto begin = _effects.begin();
        while(begin != _effects.end())
        {
            Effect& e = **begin;
            e.sprite.update(deltaTime);
            if(e.sprite.getStatus() != sfutils::AnimatedSprite::Status::Playing)
            {
                begin = _effects.erase(begin);
                _entitiesLayer->remove(&e);
                delete &e;
            }
            else
                ++begin;
        }

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

                std::list<Entity*> pick = _byCoords[coord];
                for(Entity* e : pick)
                {
                    onPickup(e->id(),coord);
                }
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

    void Level::processNetworkEvent(packet::NetworkEvent* msg)
    {
        switch(msg->type())
        {
            case FuncIds::IdDestroyEntity :
            {
                packet::DestroyEntity* event = static_cast<packet::DestroyEntity*>(msg);
                for(std::uint32_t id : event->getDestroy())
                {
                    destroyEntity(id);
                }
            }break;
            case FuncIds::IdCreateEntity :
            {
                packet::CreateEntity* event = static_cast<packet::CreateEntity*>(msg);
                for(const packet::CreateEntity::Data& data : event->getCreates())
                {
                    Entity& e = createEntity(data.entityId,data.coord);
                    makeAs(data.entityType,e,&_teamInfo.at(data.entityTeam),*this,data);
                }
            }break;
            case FuncIds::IdUpdateEntity :
            {
                packet::UpdateEntity* event = static_cast<packet::UpdateEntity*>(msg);
                for(const packet::UpdateEntity::Data& data : event->getUpdates())
                {
                    if(entities.isValid(data.entityId))
                    {
                        CompSkin::Handle skin = entities.getComponent<CompSkin>(data.entityId);
                        CompHp::Handle hp = entities.getComponent<CompHp>(data.entityId);

                        sf::Vector2i coord = _map->mapPixelToCoords(skin->_sprite.getPosition());

                        skin->_sprite.setAnimation(skin->_animations.at(data.animationId));
                        skin->_sprite.setPosition(data.position);
                        setPosition(entities.get(data.entityId),coord,data.coord);
                        hp->_hp = data.hp;
                    }
                }
            }break;
            case FuncIds::IdOnHittedEntity :
            {
                packet::OnHittedEntity* event = static_cast<packet::OnHittedEntity*>(msg);
                for(const packet::OnHittedEntity::Data& data : event->getHitted())
                {
                    if(entities.isValid(data.entityId))
                    {
                        Entity& e = entities.get(data.entityId);
                        if(e.onHitted and entities.isValid(data.enemyId))
                        {
                            Entity& enemy = entities.get(data.enemyId);
                            e.onHitted(e,_map->mapPixelToCoords(e.getPosition()),
                                       enemy, _map->mapPixelToCoords(enemy.getPosition()),
                                       *this);
                        }
                    }
                }
            }break;
            case FuncIds::IdOnHitEntity :
            {
                packet::OnHitEntity* event = static_cast<packet::OnHitEntity*>(msg);
                for(const packet::OnHitEntity::Data& data : event->getHit())
                {
                    if(entities.isValid(data.entityId))
                    {
                        Entity& e = entities.get(data.entityId);
                        if(e.onHit and entities.isValid(data.enemyId))
                        {
                            Entity& enemy = entities.get(data.enemyId);
                            e.onHit(e,_map->mapPixelToCoords(e.getPosition()),
                                       enemy, _map->mapPixelToCoords(enemy.getPosition()),
                                       *this);
                        }
                    }
                }
            }break;
            case FuncIds::IdOnSpawnEntity :
            {
                packet::OnSpawnEntity* event = static_cast<packet::OnSpawnEntity*>(msg);
                for(unsigned int id : event->getSpawn())
                {
                    if(entities.isValid(id))
                    {
                        Entity& e = entities.get(id);
                        CompAISpawner::Handle spawn = entities.getComponent<CompAISpawner>(id);
                        if(spawn.isValid() and spawn->_onSpawn)
                        {
                            spawn->_onSpawn(*this,_map->mapPixelToCoords(e.getPosition()));
                        }
                    }
                }
            }break;
            default : break;
        }
    }

    void Level::draw(sf::RenderTarget& window)
    {
        _viewer.draw();
    }

    sfutils::Layer<sf::ConvexShape>& Level::getHighlightLayer()const
    {
        return *_mouseLayer;
    }

    const sf::ConvexShape Level::getShape()const
    {
        return _map->getShape();
    }

    sfutils::EntityManager<Entity>& Level::entityManager()
    {
        return entities;
    }

    
    void Level::createSound(Configuration::Sounds sound_id,const sf::Vector2i& coord)
    {
        sf::Vector2f pos = _map->mapCoordsToPixel(coord);
        createSound(sound_id,pos);
    }

    void Level::createSound(Configuration::Sounds sound_id,const sf::Vector2f& pos)
    {
        std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds.get(sound_id)));

        sound->setPosition(pos.x,pos.y,0);
        sound->setRelativeToListener(false);
        sound->setVolume(100);
        sound->setMinDistance(300);
        sound->setAttenuation(1);

        sound->play();
        _sounds.emplace_back(std::move(sound));
    }

    void Level::addEffect(std::function<Effect*(void)> effectFn,const sf::Vector2i& coord)
    {
        Effect* effect = effectFn();

        effect->setPosition(_map->mapCoordsToPixel(coord));

        _entitiesLayer->add(effect,false);
        _effects.emplace_back(effect);
    }

    sf::Vector2i Level::getMinCoord()const
    {
        return sf::Vector2i(0,0);
    }

    sf::Vector2i Level::getMaxCoord()const
    {
        return sf::Vector2i(99,99);
    }

    sf::Vector2i Level::mapPixelToCoords(const sf::Vector2f& pos)const
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


    Entity& Level::createEntity(unsigned int id,const sf::Vector2i& coord)
    {
        entities.emplace(id);
        Entity& e = entities.get(id);

        e.add<CompSkin>();
        e.setPosition(_map->mapCoordsToPixel(coord));

        _entitiesLayer->add(&e,false);
        _byCoords[coord].emplace_back(&e);

        return e;
    }

    void Level::destroyEntity(std::uint32_t id)
    {
        const sf::Vector2i coord = _map->mapPixelToCoords(entities.getComponent<CompSkin>(id)->_sprite.getPosition());
        Entity& e = entities.get(id);

        _entitiesLayer->remove(&e,false);
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
    }
}
