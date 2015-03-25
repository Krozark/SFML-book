#ifndef SMFL_UTILS_ACTION_HPP
#define SMFL_UTILS_ACTION_HPP

#include <SFML/Window/Event.hpp>

namespace sfutils
{
    class Action
    {
        public:
            enum Type
            {
                RealTime=1,
                Pressed=1<<1,
                Released=1<<2
            };
            
            Action(const Action& other);
            Action& operator=(const Action& other);

            /*Action(const sf::Event& event,int type=Type::RealTime);
            Action(sf::Event&& event,int type=Type::RealTime);*/

            Action(const sf::Event::EventType& event);
            Action(const sf::Keyboard::Key& key,int type=Type::RealTime|Type::Pressed);
            Action(const sf::Mouse::Button& button,int type=Type::RealTime|Type::Pressed);
            Action(int joyID,unsigned int button,int type=Type::RealTime|Type::Pressed);

            bool test()const;

            bool operator==(const sf::Event& event)const;
            bool operator==(const Action& other)const;


        private:
            template<typename> friend class ActionTarget;
            sf::Event _event;
            int _type;
    };
}
#endif
