#ifndef BOOK_CONNECTION_HPP
#define BOOK_CONNECTION_HPP

#include <SFML/Network.hpp>
#include <SFML-Book/common/Packet.hpp>

#include <queue>

namespace book
{
    class Connection
    {
        public:
            Connection();
            Connection(const Connection&) = delete;
            Connection& operator=(const Connection&) = delete;

            virtual ~Connection();

            
            void run();
            void stop();
            void wait();

            int id()const;

            bool pollEvent(sf::Packet& event);
            bool pollEvent(packet::NetworkEvent*& event);
            
            void send(sf::Packet& packet);

            void disconnect();


            virtual sf::IpAddress getRemoteAddress()const = 0;

        protected:
            sf::TcpSocket _sockIn;
            sf::TcpSocket _sockOut; 

        private:
            bool _isRunning;
        
            void _receive();
            sf::Thread _receiveThread;
            sf::Mutex _receiveMutex;
            std::queue<sf::Packet> _incoming;

            void _send();
            sf::Thread _sendThread;
            sf::Mutex _sendMutex;
            std::queue<sf::Packet> _outgoing;

            static int _numberOfCreations;
            const int _id;

    };
}
#endif
