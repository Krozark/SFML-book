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
            sfutils::Frame _frameTop;
            sfutils::Label* _labelGold;

            sfutils::Frame _frameLeft;
            sfutils::AnimatedSprite _sprite;
            sfutils::TextButton* _buttonDeleteEntity;

            sf::Color _color;
            std::uint32_t _entityId;
            sfutils::EntityManager<Entity>* _entityManager;


            void initTopBar();
            void initLeftBar();
    };
}
#endif
