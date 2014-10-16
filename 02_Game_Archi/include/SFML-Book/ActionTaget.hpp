#ifndef BOOK_ACTIONTAGET_HPP
#define BOOK_ACTIONTAGET_HPP

#include <functional> //function
#include <utility> //pair
#include <list> //list

#include <SFML-Book/Action.hpp>

namespace book
{
    class ActionTaget
    {
        public:
            ActionTaget();

            bool processEvent(const sf::Event& event)const;
            void processEvents()const;

            void bind(const book::Action& action,const std::function<void(const sf::Event&)>& callback);
            void unbind(const book::Action& action);

            void map(const std::string Key,const Action& action);

        private:
            std::list<std::pair<book::Action,std::function<void(const sf::Event&)>>> _events_real_time;
            std::list<std::pair<book::Action,std::function<void(const sf::Event&)>>> _events_poll;
    };
}
#endif
