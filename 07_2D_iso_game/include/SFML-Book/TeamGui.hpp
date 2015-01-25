#ifndef BOOK_TEAMGUI_HPP
#define BOOK_TEAMGUI_HPP

#include <SFML-utils/Gui.hpp>
#include <SFML-utils/ES.hpp>

#include <SFML-Book/Entity.hpp>

namespace book
{
    class TeamGui
    {
        public:
            TeamGui(const TeamGui&) = delete;
            TeamGui& operator=(const TeamGui&) = delete;

            TeamGui(sf::RenderWindow& window,const sf::Color& color);

            void update(sf::Time deltaTime);
            bool processEvent(sf::Event& event);
            void processEvents();
            void draw(sf::RenderTarget& window);
            
            void setGold(int amount);
            const sf::Color& getColor()const;
            
            void setSelected(std::uint32_t id,sfutils::EntityManager<Entity>& manager);

        private:
            sfutils::Frame _infoBar;
            sfutils::Label* _labelGold;

            sfutils::Frame _selectBar;
            sfutils::AnimatedSprite _sprite;
            sfutils::Label* _entityName;

            std::uint32_t _entityId;
            sfutils::EntityManager<Entity>* _entityManager;

            sf::Color _color;



            void initInfoBar();
            void initSelectingBar();

            enum Status {
                None,
                Selecting,
                Building,
                Exit
            } _status;

            void unSelect();
    };
}
#endif
