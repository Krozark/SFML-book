#ifndef SMFL_UTILS_ACTIONTAGET_HPP
#define SMFL_UTILS_ACTIONTAGET_HPP

#include <SFML-utils/core/ActionMap.hpp>

#include <functional> //function
#include <utility> //pair
#include <list> //list

namespace sfutils
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
            void bind(const Action& action,const FuncType& callback);
            void bind(Action&& action,const FuncType& callback);
            void unbind(const T& key);

        private:
            std::list<std::pair<T,FuncType>> _eventsRealTime;
            std::list<std::pair<Action,FuncType>> _eventsRealTimeAction;
            std::list<std::pair<T,FuncType>> _eventsPoll;
            std::list<std::pair<Action,FuncType>> _eventsPollAction;

            const ActionMap<T>& _actionMap;
    };
}
#include <SFML-utils/core/ActionTarget.tpl>

#endif
