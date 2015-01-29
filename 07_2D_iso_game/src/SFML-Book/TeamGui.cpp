#include <SFML-Book/TeamGui.hpp>

#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Component.hpp>
#include <SFML-Book/Level.hpp>

namespace book
{
    
    TeamGui::TeamGui(sf::RenderWindow& window,const sf::Color& color) :
    _infoBar(window,Configuration::gui_inputs),
    _labelGold(nullptr),
    _selectBar(window,Configuration::gui_inputs),
    _entityName(nullptr),
    _entityHp(nullptr),
    _buildBar(window,Configuration::gui_inputs),
    _entityId(0),
    _entityManager(nullptr),
    _color(color),
    _level(nullptr),
    _selectionLight(nullptr),
    _status(Status::None)
    {
        Configuration::setGuiColor(sf::Color(color.r*0.4,
                                             color.g*0.4,
                                             color.b*0.4,
                                             240));
        initInfoBar();
        initSelectingBar();
        initBuildBar();

        _spriteBuild.setAnimation(&Configuration::animations.get(Configuration::AnimWormEggBirth));
        _spriteBuild.setScale(0.3,0.3);
        _spriteBuild.setOrigin(256*0.5,256*0.9);
    }

    void TeamGui::update(sf::Time deltaTime)
    {
        switch(_status)
        {
            case Status::Selecting :
            {
                if(_entityManager and _entityManager->isValid(_entityId))
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
                }
            }break;
            case Status::Building :
            {
                _spriteBuild.update(deltaTime);
            }break;
            default: break;
        }
    }
    
    bool TeamGui::processEvent(sf::Event& event)
    {
        bool res = _infoBar.processEvent(event);
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
                    if(event.type == sf::Event::MouseMoved)
                    {
                        sf::Vector2i coord = _level->mapScreenToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y));
                        sf::Vector2i pos = _level->mapCoordsToScreen(coord);
                        _spriteBuild.setPosition(pos.x,pos.y);
                    }
                }break;
                default: break;
            }
        }
        return res;
    }

    void TeamGui::processEvents()
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

    void TeamGui::draw(sf::RenderTarget& window)
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
                window.draw(_spriteBuild);

            }break;
            default: break;
        }
    }

    void TeamGui::setGold(int amount)
    {
        _labelGold->setText("Gold: "+std::to_string(amount));
    }

    const sf::Color& TeamGui::getColor()const
    {
        return _color;
    }

    void TeamGui::setLevel(Level* level)
    {
        if(level != _level)
        {
            unBuild();
            unSelect();
            _level = level;
        }
    }

    void TeamGui::setSelected(std::uint32_t id,sfutils::EntityManager<Entity>& manager)
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

    void TeamGui::initInfoBar()
    {
        _infoBar.setSize(sf::Vector2f(0,60));
        _infoBar.setFillColor(sf::Color(_color.r,_color.g,_color.b,128));

        sfutils::HLayout* layout = new sfutils::HLayout;
        _infoBar.setLayout(layout);

        {
            sfutils::TextButton* button = new sfutils::TextButton("Build");
            button->setCharacterSize(15);
            button->setOutlineThickness(1);
            button->on_click = [this](const sf::Event&, sfutils::Button& button){
                unSelect();
                _status = Status::Building;
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
            button->setCharacterSize(15);
            button->setOutlineThickness(1);
            button->on_click = [this](const sf::Event&, sfutils::Button& button){
                _status = Status::Exit;
            };
            layout->add(button);
        }

    }

    void TeamGui::initSelectingBar()
    {
        _selectBar.setSize(sf::Vector2f(100,300));
        _selectBar.setFillColor(sf::Color(_color.r,_color.g,_color.b,128));
        _selectBar.setPosition(0,60);

        sfutils::VLayout* layout = new sfutils::VLayout;
        _selectBar.setLayout(layout);

        {
            _entityName = new sfutils::Label("???");
            _entityName->setCharacterSize(15);
            layout->add(_entityName);
        }

        {
            _entityHp = new sfutils::Label("");
            _entityHp->setCharacterSize(15);
            layout->add(_entityHp);
        }

        {
            sfutils::TextButton* button = new sfutils::TextButton("Delete");
            button->setCharacterSize(15);
            button->setOutlineThickness(1);
            button->on_click = [this](const sf::Event&, sfutils::Button& button){
                if(_status == Status::Selecting)
                {
                    _entityManager->remove(_entityId);
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

    void TeamGui::initBuildBar()
    {
        _buildBar.setSize(sf::Vector2f(100,500));
        _buildBar.setFillColor(sf::Color(_color.r,_color.g,_color.b,128));
        _buildBar.setPosition(0,60);

        sfutils::VLayout* layout = new sfutils::VLayout;
        _buildBar.setLayout(layout);
    }

    void TeamGui::unSelect()
    {
        _entityManager = nullptr;
        _entityId = 0;

        if(_selectionLight and _level)
        {
            auto& layer = _level->getHighlightLayer();
            layer.remove(_selectionLight);
            _selectionLight = nullptr;
        }

        _status = Status::None;

    }

    void TeamGui::unBuild()
    {
        size_t size = _highlight.size();
        if(size>0 and _level)
        {
            auto& layer = _level->getHighlightLayer();
            for(size_t i=0;i<size;++i)
            {
                layer.remove(_highlight[i]);
            }
        }
        _highlight.clear();
    }

    void TeamGui::setHp(int current,int max)
    {
        _entityHp->setText("HP: "+std::to_string(current)+"/"+std::to_string(max));
    }
}
