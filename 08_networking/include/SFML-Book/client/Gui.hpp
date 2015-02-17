#ifndef BOOK_GUI_HPP
#define BOOK_GUI_HPP

#include <SFML-utils/Gui.hpp>
#include <SFML-utils/core/AnimatedSprite.hpp>

#include <SFML-Book/common/Packet.hpp>

namespace book
{
    class Client;
    class Level;

    class MainMenu : public sfutils::Frame
    {
        public:
            MainMenu(const MainMenu&) = delete;
            MainMenu& operator=(const MainMenu&) = delete;

            MainMenu(sf::RenderWindow& window,Client& client);

            void fill(packet::SetListGame& list);

        private:
            Client& _client;
    };

    class GameMenu
    {
        public:
            GameMenu(const GameMenu&) = delete;
            GameMenu& operator=(const GameMenu&) = delete;

            enum Status {
                None,
                Selecting,
                Building,
                Exit
            };

            GameMenu(sf::RenderWindow& window,Client& client,int& team);

            ~GameMenu();

            void setTeamColor(const sf::Color& color);
            void init(Level* level,int gold);

            void update(sf::Time deltaTime);
            
            bool processEvent(sf::Event& event);
            void processEvents();
            void processNetworkEvent(packet::NetworkEvent* msg);

            void draw(sf::RenderTarget& window);
            
            void setSelected(std::uint32_t id);
            
            Status getStatus()const;
            

        private:
            int& _team;
            Client& _client;
            sf::Color _color;

            sfutils::Frame _infoBar;
            sfutils::Label* _labelGold;

            sfutils::Frame _selectBar;
            sfutils::Label* _entityName;
            sfutils::Label* _entityHp;
            sfutils::AnimatedSprite _spriteInfo;

            sfutils::Frame _buildBar;
            sfutils::AnimatedSprite _spriteBuild;
            int _gold_cost;

            int _makeAs;

            int _goldCost;
            int _goldAmount;

            std::uint32_t _entityId;
            Level* _level;

            std::vector<sf::ConvexShape*> _highlight;
            sf::ConvexShape* _selectionLight;

            Status _status;


            void clear();

            void initInfoBar();
            void initSelectingBar();
            void initBuildBar();


            void unSelect();
            void unBuild();
            void setBuild();
            void setHp(int current,int max);
            void setGold(int amount);
            
    };
}
#endif
