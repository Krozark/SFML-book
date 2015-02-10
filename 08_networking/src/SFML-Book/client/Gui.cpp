#include <SFML-Book/client/Gui.hpp>

#include <SFML-Book/common/Configuration.hpp>
#include <SFML-Book/client/Client.hpp>

#include <sstream>

namespace book
{
    MainMenu::MainMenu(sf::RenderWindow& window,Client& client) : sfutils::Frame(window,Configuration::gui_inputs), _client(client)
    {
        setLayout(new sfutils::VLayout);
    }

    void MainMenu::fill(packet::SetListGame& list)
    {
        clear();

        sfutils::VLayout* layout = static_cast<sfutils::VLayout*>(Frame::getLayout());
        
        {
            sfutils::TextButton* button = new sfutils::TextButton("Create game");
            button->setCharacterSize(20);
            button->setOutlineThickness(1);
            button->setFillColor(sf::Color(48,80,197));
            button->on_click = [this](const sf::Event&, sfutils::Button& button){
                sf::Packet event;
                event<<packet::CreateGame();
                _client.send(event);
            };
            layout->add(button);
        }

        {
            sfutils::TextButton* button = new sfutils::TextButton("Refresh");
            button->setCharacterSize(20);
            button->setOutlineThickness(1);
            button->setFillColor(sf::Color(0,88,17));
            button->on_click = [this](const sf::Event&, sfutils::Button& button){
                sf::Packet event;
                event<<packet::GetListGame();
                _client.send(event);
            };
            layout->add(button);
        }

        for(const packet::SetListGame::Game& game : list.list())
        {

            std::stringstream ss;
            ss<<"Game ["<<game.id<<"] teams: "<<game.nbTeams<<" players: "<<game.nbPlayers;

            sfutils::TextButton* button = new sfutils::TextButton(ss.str());
            button->setCharacterSize(20);
            button->setOutlineThickness(1);
            button->on_click = [this,game](const sf::Event&, sfutils::Button& button){
                sf::Packet event;
                event<<packet::JoinGame(game.id);
                _client.send(event);
            };
            layout->add(button);

        }
    }
}
