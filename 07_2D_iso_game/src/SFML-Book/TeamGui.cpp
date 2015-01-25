#include <SFML-Book/TeamGui.hpp>

#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Component.hpp>

namespace book
{
    
    TeamGui::TeamGui(sf::RenderWindow& window,const sf::Color& color) : _frameTop(window,Configuration::gui_inputs), _labelGold(nullptr), _frameLeft(window,Configuration::gui_inputs), _color(color), _entityId(0),_entityManager(nullptr)
    {
        initTopBar();
        initLeftBar();

    }

    void TeamGui::update(sf::Time deltaTime)
    {
        if(_entityManager)
        {
            if(_entityManager->isValid(_entityId))
            {
                _sprite.update(deltaTime);
            }
            else
            {
                _entityManager = nullptr;
                _entityId = 0;
            }
        }
    }
    
    bool TeamGui::processEvent(sf::Event& event)
    {
        bool res = _frameTop.processEvent(event);
        if(not res and _entityManager and _entityManager->isValid(_entityId))
            res = _frameLeft.processEvent(event);
        return res;
    }

    void TeamGui::processEvents()
    {
        _frameTop.processEvents();
        if(_entityManager and _entityManager->isValid(_entityId))
        {
            _frameLeft.processEvents();
        }
    }

    void TeamGui::draw(sf::RenderTarget& window)
    {
        window.draw(_frameTop);

        if(_entityManager and _entityManager->isValid(_entityId))
        {
            window.draw(_frameLeft);
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
    }

    void TeamGui::initTopBar()
    {
        _frameTop.setSize(sf::Vector2f(0,60));
        _frameTop.setFillColor(sf::Color(_color.r,_color.b,_color.b,127));

        sfutils::HLayout* layout = new sfutils::HLayout;
        _frameTop.setLayout(layout);

        //init gold
        _labelGold = new sfutils::Label("");
        _labelGold->setCharacterSize(15);
        _labelGold->setTextColor(sf::Color(216,171,44));//golden
        layout->add(_labelGold);
        setGold(0);

    }

    void TeamGui::initLeftBar()
    {
        _frameLeft.setSize(sf::Vector2f(100,-60));
        _frameLeft.setFillColor(sf::Color(_color.r,_color.b,_color.b,127));
        _frameLeft.setPosition(0,60);

        sfutils::VLayout* layout = new sfutils::VLayout;
        _frameLeft.setLayout(layout);

        _buttonDeleteEntity = new sfutils::TextButton("Delete");
        _buttonDeleteEntity->setCharacterSize(20);
        _buttonDeleteEntity->setOutlineThickness(1);
        _buttonDeleteEntity->on_click = [this](const sf::Event&, sfutils::Button& button){
            if(_entityManager and _entityManager->isValid(_entityId))
            {
                _entityManager->remove(_entityId);
            }
        };

        layout->add(_buttonDeleteEntity);
    }
}
