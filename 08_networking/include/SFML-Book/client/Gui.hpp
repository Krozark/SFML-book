#ifndef BOOK_GUI_HPP
#define BOOK_GUI_HPP

#include <SFML-utils/Gui.hpp>

#include <SFML-Book/common/Packet.hpp>

namespace book
{
    class Client;
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
}
#endif
