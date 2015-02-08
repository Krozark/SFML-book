#ifndef BOOK_CLIENT_HPP
#define BOOK_CLIENT_HPP

#include <SFML/Network.hpp>
#include <queue>

namespace book
{
    class Team;
    class NetworkEvent;

    class Client
    {
        public:
            Client();
            Client(const Client&) = delete;
            Client& operator=(const Client&) = delete;

            
            void run();
            void stop();
            unsigned int id()const;

            bool poolEvent(sf::Packet& event);
            void send(sf::Packet& packet);
            

        private:
            friend class Server;


            bool _isRunning;
        
            void _receive();
            sf::TcpSocket _sockIn;
            sf::Thread _receiveThread;
            sf::Mutex _receiveMutex;
            std::queue<sf::Packet> _incomming;

            void _send();
            sf::TcpSocket _sockOut; 
            sf::Thread _sendThread;
            sf::Mutex _sendMutex;
            std::queue<sf::Packet> _outgoing;

            static unsigned int _numberOfCreations;
            const unsigned int _id;

    };
}
#endif
