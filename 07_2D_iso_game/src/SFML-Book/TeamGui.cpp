#include <SFML-Book/TeamGui.hpp>

#include <SFML-Book/Configuration.hpp>

namespace book
{
    
    TeamGui::TeamGui(sf::RenderWindow& window,const sf::Color& color) : _frame(window,Configuration::gui_inputs), _color(color)
    {
        _frame.setSize(sf::Vector2f(0,50));
        _frame.setFillColor(sf::Color(color.r,color.b,color.b,127));

        sfutils::HLayout* layout = new sfutils::HLayout;
        _labelGold = new sfutils::Label("0");
        _labelGold->setCharacterSize(20);
        _labelGold->setTextColor(sf::Color(216,171,44));//golden
        layout->add(_labelGold);

        _frame.setLayout(layout);
    }
    
    bool TeamGui::processEvent(sf::Event& event)
    {
        return _frame.processEvent(event);
    }

    void TeamGui::processEvents()
    {
        _frame.processEvents();
    }

    void TeamGui::draw(sf::RenderTarget& window)
    {
        window.draw(_frame);
    }

    void TeamGui::setGold(int amount)
    {
        _labelGold->setText(std::to_string(amount));
    }
    const sf::Color& TeamGui::getColor()const
    {
        return _color;
    }
}
