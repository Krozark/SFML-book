#include <SFML-Book/TeamGui.hpp>

#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Component.hpp>

namespace book
{
    
    TeamGui::TeamGui(sf::RenderWindow& window,const sf::Color& color) : _infoBar(window,Configuration::gui_inputs),
    _labelGold(nullptr),
    _selectBar(window,Configuration::gui_inputs),
    _entityName(nullptr),
    _entityId(0),
    _entityManager(nullptr),
    _color(color),
    _status(Status::None)
    {
        Configuration::setGuiColor(sf::Color(color.r*0.4,
                                             color.g*0.4,
                                             color.b*0.4,
                                             240));
        initInfoBar();
        initSelectingBar();
    }

    void TeamGui::update(sf::Time deltaTime)
    {
        Status old = _status;
        if(_entityManager and _entityManager->isValid(_entityId))
        {
            _status = Status::Selecting;
            _sprite.update(deltaTime);

            CompHp::Handle hp = _entityManager->getComponent<CompHp>(_entityId);
            if(hp.isValid())
                setHp(hp->_hp,hp->_maxHp);
            else
                _entityHp->setText("HP: ?/?");
        }
        else
            _status = Status::None;

        if(old == Status::Selecting and old != _status)
            unSelect();
    }
    
    bool TeamGui::processEvent(sf::Event& event)
    {
        bool res = _infoBar.processEvent(event);
        if(_status == Status::Selecting)
            res = _selectBar.processEvent(event);
        return res;
    }

    void TeamGui::processEvents()
    {
        _infoBar.processEvents();
        if(_status == Status::Selecting)
        {
            _selectBar.processEvents();
        }
    }

    void TeamGui::draw(sf::RenderTarget& window)
    {
        window.draw(_infoBar);

        if(_status == Status::Selecting)
        {
            window.draw(_selectBar);
            window.draw(_sprite);
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

    void TeamGui::setSelected(std::uint32_t id,sfutils::EntityManager<Entity>& manager)
    {
        _entityId = id;
        _entityManager = &manager;

        _sprite = manager.getComponent<CompSkin>(id)->_sprite;

        _sprite.setColor(sf::Color(255,255,255,255));
        _sprite.setOrigin(0,0);
        _sprite.setPosition(5,5);

        sf::IntRect rect = _sprite.getAnimation()->getRect(0);
        _sprite.setScale(sf::Vector2f(90.f/rect.width,90.f/rect.height));

        Entity& e = manager.get(id);
        _entityName->setText(e.name);

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

    void TeamGui::unSelect()
    {
        _entityManager = nullptr;
        _entityId = 0;
        _status = Status::None;
    }
    void TeamGui::setHp(int current,int max)
    {
        _entityHp->setText("HP: "+std::to_string(current)+"/"+std::to_string(max));
    }
}
