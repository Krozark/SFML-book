#ifndef BOOK_TEAMGUI_HPP
#define BOOK_TEAMGUI_HPP

#include <SFML-utils/Gui.hpp>

namespace book
{
    class TeamGui
    {
        public:
            TeamGui(const TeamGui&) = delete;
            TeamGui& operator=(const TeamGui&) = delete;

            TeamGui(sf::RenderWindow& window,const sf::Color& color);

            bool processEvent(sf::Event& event);
            void processEvents();
            void draw(sf::RenderTarget& window);
            
            void setGold(int amount);
            const sf::Color& getColor()const;

        private:
            sfutils::Frame _frame;
            
            sfutils::Label* _labelGold;

            sf::Color _color;
    };
}
#endif
