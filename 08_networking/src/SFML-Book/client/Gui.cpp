#include <SFML-Book/client/Gui.hpp>

#include <SFML-Book/common/Configuration.hpp>
#include <SFML-Book/client/Client.hpp>

#include <sstream>

namespace book
{
    MainMenu::MainMenu(sf::RenderWindow& window,Client& client) : sfutils::Frame(window,Configuration::gui_inputs), _client(client)
    {
        setLayout(new sfutils::VLayout);
    }

    void MainMenu::fill(packet::SetListGame& list)
    {
        clear();

        sfutils::VLayout* layout = static_cast<sfutils::VLayout*>(Frame::getLayout());
        
        {
            sfutils::TextButton* button = new sfutils::TextButton("Create game");
            button->setCharacterSize(20);
            button->setOutlineThickness(1);
            button->setFillColor(sf::Color(48,80,197));
            button->on_click = [this](const sf::Event&, sfutils::Button& button){
                sf::Packet event;
                event<<packet::CreateGame();
                _client.send(event);
            };
            layout->add(button);
        }

        {
            sfutils::TextButton* button = new sfutils::TextButton("Refresh");
            button->setCharacterSize(20);
            button->setOutlineThickness(1);
            button->setFillColor(sf::Color(0,88,17));
            button->on_click = [this](const sf::Event&, sfutils::Button& button){
                sf::Packet event;
                event<<packet::GetListGame();
                _client.send(event);
            };
            layout->add(button);
        }

        for(const packet::SetListGame::Game& game : list.list())
        {

            std::stringstream ss;
            ss<<"Game ["<<game.id<<"] teams: "<<game.nbTeams<<" players: "<<game.nbPlayers;

            sfutils::TextButton* button = new sfutils::TextButton(ss.str());
            button->setCharacterSize(20);
            button->setOutlineThickness(1);
            button->on_click = [this,game](const sf::Event&, sfutils::Button& button){
                sf::Packet event;
                event<<packet::JoinGame(game.id);
                _client.send(event);
            };
            layout->add(button);

        }
    }

    //////////////////// GameMenu ///////////////////////

    GameMenu::GameMenu(sf::RenderWindow& window,Client& client) : 
        _client(client),
        _infoBar(window,Configuration::gui_inputs),
        _labelGold(nullptr),
        _selectBar(window,Configuration::gui_inputs),
        _entityName(nullptr),
        _entityHp(nullptr),
        _buildBar(window,Configuration::gui_inputs),
        _status(Status::None)
    {
    }

    GameMenu::~GameMenu()
    {
        clear();
    }

    void GameMenu::setTeamColor(const sf::Color& color)
    {
        _color = color;
        Configuration::setGuiColor(sf::Color(color.r*0.4,
                                             color.g*0.4,
                                             color.b*0.4,
                                             240));
        
    }

    void GameMenu::init()
    {

        clear();

        unBuild();
        unSelect();

        initInfoBar();
        initSelectingBar();
        initBuildBar();

        //IdDisconnected
        //IdCreateEntity
        //IdDestroyEntity
    }

    void GameMenu::clear()
    {
    }

    void GameMenu::update(sf::Time deltaTime)
    {
        switch(_status)
        {
            case Status::Selecting :
            {
                /*if(_entityManager and _entityManager->isValid(_entityId))
                {
                    _spriteInfo.update(deltaTime);

                    CompHp::Handle hp = _entityManager->getComponent<CompHp>(_entityId);

                    if(hp.isValid())
                        setHp(hp->_hp,hp->_maxHp);
                    else
                        _entityHp->setText("HP: ?/?");

                    CompSkin::Handle skin = _entityManager->getComponent<CompSkin>(_entityId);
                    _selectionLight->setPosition(skin->_sprite.getPosition());

                }
                else
                {
                    unSelect();
                }*/
            }break;
            case Status::Building :
            {
                /*if(_makeAs != nullptr)
                {
                    if(_gold_cost <= _team._gold)
                    {
                        _spriteBuild.setColor(sf::Color::White);
                    }
                    else
                    {
                        _spriteBuild.setColor(sf::Color::Red);
                    }
                    _spriteBuild.update(deltaTime);
                }*/
            }break;
            default: break;
        }
    }

    bool GameMenu::processEvent(sf::Event& event)
    {
        bool res = false;
        res = _infoBar.processEvent(event);
        if(not res)
        {
            switch (_status)
            {
                case Status::Selecting :
                {
                    res = _selectBar.processEvent(event);
                }break;
                case Building :
                {
                    res = _buildBar.processEvent(event);
                    /*if(_makeAs != nullptr)
                    {
                        if(event.type == sf::Event::MouseMoved)
                        {
                            sf::Vector2i mouse = sf::Vector2i(event.mouseMove.x,event.mouseMove.y);
                            sf::Vector2i coord = _level->mapScreenToCoords(mouse);
                            sf::Vector2i pos = _level->mapCoordsToScreen(coord);
                            _spriteBuild.setPosition(pos.x,pos.y);
                        }
                        else if(event.type == sf::Event::MouseButtonPressed )
                        {
                            sf::Vector2i mouse = sf::Vector2i(event.mouseButton.x,event.mouseButton.y);
                            sf::Vector2i coord = _level->mapScreenToCoords(mouse);
                            if(_makeAs != nullptr and _level != nullptr and _gold_cost <= _team._gold)
                            {
                                size_t size = _highlight.size();
                                for(size_t i=0;i<size;++i)
                                {
                                    sf::Vector2i shapeCoord = _level->mapPixelToCoords(_highlight[i]->getPosition());
                                    if(coord == shapeCoord)
                                    {
                                        Entity& entity = _level->createEntity(coord);
                                        _makeAs(entity,&_team,*_level);
                                        _team.addGold(-_gold_cost);

                                        setBuild();
                                        break;
                                    }
                                }

                            }
                        }
                    }*/
                }break;
                default: break;
            }
        }
        return res;
    }

    void GameMenu::processEvents()
    {
        _infoBar.processEvents();
        switch (_status)
        {
            case Status::Selecting :
            {
                _selectBar.processEvents();
            }break;
            case Building :
            {
                _buildBar.processEvents();
            }break;
            default: break;
        }
    }
    
    void GameMenu::processNetworkEvent(packet::NetworkEvent* msg)
    {
        //IdAddGoldTeam
    }

    void GameMenu::draw(sf::RenderTarget& window)
    {
        window.draw(_infoBar);

        switch (_status)
        {
            case Status::Selecting :
            {
                window.draw(_selectBar);
                window.draw(_spriteInfo);
            }break;
            case Building :
            {
                window.draw(_buildBar);
                /*if(_makeAs != nullptr)
                {
                    window.draw(_spriteBuild);
                }*/

            }break;
            default: break;
        }
    }

    /*void GameMenu::setSelected(std::uint32_t id,sfutils::EntityManager<Entity>& manager)
    {
        if(_status == Status::None or _status == Status::Selecting)
        {
            unSelect();
            unBuild();

            _entityId = id;
            _entityManager = &manager;

            _spriteInfo = manager.getComponent<CompSkin>(id)->_sprite;

            _spriteInfo.setColor(sf::Color(255,255,255,255));
            _spriteInfo.setOrigin(0,0);
            _spriteInfo.setPosition(5,5);

            sf::IntRect rect = _spriteInfo.getAnimation()->getRect(0);
            _spriteInfo.setScale(sf::Vector2f(90.f/rect.width,90.f/rect.height));

            Entity& e = manager.get(id);
            _entityName->setText(e.name);


            //hightlight
            if(_level)
            {
                _selectionLight = _level->getHighlightLayer().add(_level->getShape());
                _selectionLight->setFillColor(sf::Color(_color.r,_color.g,_color.b,128));
            }

            _status = Status::Selecting;
        }
    }*/

    void GameMenu::initInfoBar()
    {
        _infoBar.setSize(sf::Vector2f(0,60));
        _infoBar.setFillColor(sf::Color(_color.r,_color.g,_color.b,128));

        sfutils::HLayout* layout = new sfutils::HLayout;
        _infoBar.setLayout(layout);

        {
            sfutils::TextButton* button = new sfutils::TextButton("Build");
            button->setCharacterSize(20);
            button->setOutlineThickness(1);
            button->on_click = [this](const sf::Event&, sfutils::Button& button){
                setBuild();
            };
            layout->add(button);
        }

        //init gold
        {
            _labelGold = new sfutils::Label("");
            _labelGold->setCharacterSize(20);
            _labelGold->setTextColor(sf::Color(216,171,44));//golden
            layout->add(_labelGold);
            setGold(0);
        }

        {
            sfutils::TextButton* button = new sfutils::TextButton("Exit");
            button->setCharacterSize(20);
            button->setOutlineThickness(1);
            button->on_click = [this](const sf::Event&, sfutils::Button& button){
                _status = Status::Exit;
            };
            layout->add(button);
        }

    }

    void GameMenu::initSelectingBar()
    {
        _selectBar.setSize(sf::Vector2f(120,300));
        _selectBar.setFillColor(sf::Color(_color.r,_color.g,_color.b,128));
        _selectBar.setPosition(0,60);

        sfutils::VLayout* layout = new sfutils::VLayout;
        _selectBar.setLayout(layout);

        {
            _entityName = new sfutils::Label("???");
            _entityName->setCharacterSize(20);
            layout->add(_entityName);
        }

        {
            _entityHp = new sfutils::Label("");
            _entityHp->setCharacterSize(20);
            layout->add(_entityHp);
        }

        {
            sfutils::TextButton* button = new sfutils::TextButton("Delete");
            button->setCharacterSize(15);
            button->setOutlineThickness(1);
            button->on_click = [this](const sf::Event&, sfutils::Button& button){
                if(_status == Status::Selecting)
                {
                    //TODO _level->destroyEntity(_entityId);
                    unSelect();
                }
            };
            layout->add(button);
        }
        {
            sfutils::TextButton* close = new sfutils::TextButton("close");
            close->setCharacterSize(15);
            close->setOutlineThickness(1);
            close->on_click = [this](const sf::Event&, sfutils::Button& button){
                this->unSelect();
            };
            layout->add(close);
        }
    } 

    void GameMenu::initBuildBar()
    {
        _buildBar.setSize(sf::Vector2f(200,600));
        _buildBar.setFillColor(sf::Color(_color.r,_color.g,_color.b,128));
        _buildBar.setPosition(0,60);

        sfutils::VLayout* layout = new sfutils::VLayout;
        _buildBar.setLayout(layout);

        /*for(Info& info : informations)
        {//worms egg
            sfutils::SpriteButton* button = new sfutils::SpriteButton(Configuration::textures.get(info.icon_id));
            button->on_click = [this,info](const sf::Event& event,sfutils::Button& button){
                this->_spriteBuild.setAnimation(&Configuration::animations.get(info.animation_id));

                sf::IntRect rec = _spriteBuild.getAnimation()->getRect(0);
                this->_spriteBuild.setOrigin(rec.width*0.5,rec.height*0.8);
                this->_spriteBuild.setScale(0.3,0.3);

                this->_gold_cost = info.cost;
                this->_makeAs = info.makeAs;
            };
            layout->add(button);

            sfutils::Label* desc = new sfutils::Label(info.name
                                                      +"\nCost: "+std::to_string(info.cost)
                                                      +"\n"+info.description);
            desc->setCharacterSize(18);
            layout->add(desc);
        }*/

        {
            sfutils::TextButton* close = new sfutils::TextButton("close");
            close->setCharacterSize(20);
            close->setOutlineThickness(1);
            close->on_click = [this](const sf::Event&, sfutils::Button& button){
                this->unBuild();
            };
            layout->add(close);
        }
    }

    void GameMenu::unSelect()
    {
        /*_entityManager = nullptr;
        _entityId = 0;

        if(_selectionLight and _level)
        {
            auto& layer = _level->getHighlightLayer();
            layer.remove(_selectionLight);
            _selectionLight = nullptr;
        }*/

        _status = Status::None;

    }

    void GameMenu::unBuild()
    {
        /*size_t size = _highlight.size();
        if(size>0 and _level)
        {
            auto& layer = _level->getHighlightLayer();
            for(size_t i=0;i<size;++i)
            {
                layer.remove(_highlight[i]);
            }
        }
        _highlight.clear();*/

        _status = Status::None;
    }

    void GameMenu::setBuild()
    {
        unSelect();
        unBuild();

        _status = Status::Building;
        /*_makeAs = nullptr;

        CompBuildArea::Handle area;
        CompTeam::Handle team;
        CompSkin::Handle skin;
        
        auto view = _level->entityManager().getByComponents(area,team,skin);
        auto end = view.end();

        std::set<sf::Vector2i,cmpVector2i>pos_set;
        std::set<sf::Vector2i,cmpVector2i>pos_set_not_allow;

        sf::Vector2i min = _level->getMinCoord();
        sf::Vector2i max = _level->getMaxCoord();

        for(auto begin = view.begin();begin != end;++begin)
        {
            sf::Vector2f initPos = skin->_sprite.getPosition();
            sf::Vector2i initCoords = _level->mapPixelToCoords(initPos);
            pos_set_not_allow.emplace(initCoords); //romove all already used tile

            if(team->_team->id() == _team.id() and area->_range > 0)
            {


                int range = area->_range;
                for(int x =-range; x<=range;++x)
                {
                    int m = std::min(range,-x+range);

                    for(int y = std::max(-range,-x-range);y<=m;++y)
                    {
                        if(x != 0 or y != 0)
                        {
                            sf::Vector2i coord = initCoords + sf::Vector2i(x,y);
                            if((coord.x >= min.x and coord.y >= min.y)
                               and (coord.x <= max.y and coord.y <= max.y))
                            {
                                pos_set.emplace(coord);
                            }
                        }
                    }
                }
            }
        }

        for(const sf::Vector2i& pos : pos_set_not_allow)
            pos_set.erase(pos);

        for(const sf::Vector2i& pos : pos_set)
        {
            sf::ConvexShape* shape = _level->getHighlightLayer().add(_level->getShape());
            shape->setFillColor(sf::Color(0,255,0,128));
            shape->setPosition(_level->mapCoordsToPixel(pos));
            _highlight.emplace_back(shape);
        }*/
    }




    void GameMenu::setGold(int amount)
    {
        _labelGold->setText("Gold: "+std::to_string(amount));
    }



}
