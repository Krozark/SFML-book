#ifndef BOOK_CLIENT_HPP
#define BOOK_CLIENT_HPP

#include <SFML-Book/common/Connection.hpp>
#include <SFML-Book/server/Team.hpp>

namespace book
{
    class Client : public Connection
    {
        public:
            Client(const Client&) = delete;
            Client& operator=(const Client&) = delete;

            Client();
            ~Client();

            void setTeam(Team::type_ptr team);
            Team::type_ptr getTeam()const;

            bool connect();
            virtual sf::IpAddress getRemoteAddress()const;

            sf::TcpSocket& getSockIn();
        private:
            Team::type_ptr _team;

    };
}
#endif
