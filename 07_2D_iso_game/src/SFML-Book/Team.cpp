
#include <SFML-Book/Team.hpp>

namespace book
{
    Team::Team(sf::RenderWindow& window,int id,const sf::Color& color) : _id(id), _points(0), _gold(0), _gui(window,color)
    {
    }

    void Team::addGold(int amount)
    {
        if(amount > 0)
        {
            _gold += amount;
            _gui.setGold(_gold);
        }
    }

    const sf::Color& Team::getColor()const
    {
        return _gui.getColor();
    }

    bool Team::processEvent(sf::Event& event)
    {
        return _gui.processEvent(event);
    }

    void Team::processEvents()
    {
        _gui.processEvents();
    }

    void Team::draw(sf::RenderTarget& target)
    {
        _gui.draw(target);
    }
}
