#ifndef BOOK_ACTION_HPP
#define BOOK_ACTION_HPP

#include <SFML/Window/Event.hpp>

namespace book
{
    class Action
    {
        public:
            enum Type {RealTime=0b100,Press=0b010,Release=0b001};
            
            Action(const Action& other);
            Action& operator=(const Action& other);

            /*Action(const sf::Event& event,int type=Type::RealTime);
            Action(sf::Event&& event,int type=Type::RealTime);

            Action(const sf::Event::EventType& event,int type=Type::Press);*/
            Action(const sf::Keyboard::Key& key,int type=Type::RealTime|Type::Press);
            Action(const sf::Mouse::Button& button,int type=Type::RealTime|Type::Press);

            bool test()const;

            bool operator==(const sf::Event& event)const;
            bool operator==(const Action& other)const;


        private:
            friend class ActionTaget;
            sf::Event _event;
            int _type;
    };
}
#endif
