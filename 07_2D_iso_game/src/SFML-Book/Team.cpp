
#include <SFML-Book/Team.hpp>

namespace book
{
    Team::Team(sf::RenderWindow& window,int id,const sf::Color& color) : gui(window,color),_id(id), _points(0), _gold(0)
    {
    }

    void Team::addGold(int amount)
    {
        if(amount > 0)
        {
            _gold += amount;
            gui.setGold(_gold);
        }
    }

    int Team::id()const
    {
        return _id;
    }
}
