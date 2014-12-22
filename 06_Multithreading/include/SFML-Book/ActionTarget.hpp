#ifndef BOOK_ACTIONTAGET_HPP
#define BOOK_ACTIONTAGET_HPP

#include <SFML-Book/ActionMap.hpp>

#include <functional> //function
#include <utility> //pair
#include <list> //list

namespace book
{
    template<typename T = int>
    class ActionTarget
    {
        public:
            ActionTarget(const ActionTarget<T>&) = delete;
            ActionTarget<T>& operator=(const ActionTarget<T>&) = delete;

            using FuncType = std::function<void(const sf::Event&)>;

            ActionTarget(const ActionMap<T>& map);

            bool processEvent(const sf::Event& event)const;
            void processEvents()const;

            void bind(const T& key,const FuncType& callback);
            void unbind(const T& key);

        private:
            std::list<std::pair<T,FuncType>> _events_real_time;
            std::list<std::pair<T,FuncType>> _events_poll;

            const ActionMap<T>& _action_map;
    };
}
#include <SFML-Book/ActionTarget.tpl>

#endif
