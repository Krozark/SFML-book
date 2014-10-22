#ifndef BOOK_ACTIONMAP_HPP
#define BOOK_ACTIONMAP_HPP

#include <SFML-Book/Action.hpp>

#include <unordered_map> //unordered_map

namespace book
{
    template<typename T = int>
    class ActionMap
    {
        public:
            ActionMap(const ActionMap<T>&) = delete;
            ActionMap<T>& operator=(const ActionMap<T>&) = delete;

            ActionMap() = default;

            void map(const T& key,const Action& action);
            const Action& get(const T& key)const;

        private:
            std::unordered_map<T,Action> _map;
    };
}
#include <SFML-Book/ActionMap.tpl>

#endif
