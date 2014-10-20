namespace book
{
    template<typename T>
    ActionTarget<T>::ActionTarget(const ActionMap<T>& map) : _action_map(map)
    {
    }

    template<typename T>
    bool ActionTarget<T>::processEvent(const sf::Event& event)const
    {
        bool res = false;
        for(auto& pair : _events_poll)
        {
            if(_action_map.get(pair.first) == event)
            {
                pair.second(event);
                res = true;
                break;
            }
        }
        return res;
    }

    template<typename T>
    void ActionTarget<T>::processEvents()const
    {
        for(auto& pair : _events_real_time)
        {
            const Action& action = _action_map.get(pair.first);
            if(action.test())
                pair.second(action._event);
        }
    }

    template<typename T>
    void ActionTarget<T>::bind(const T& key,const FuncType& callback)
    {
        const Action& action = _action_map.get(key);
        if(action._type & Action::Type::RealTime)
            _events_real_time.emplace_back(key,callback);
        else
            _events_poll.emplace_back(key,callback);
    }

    template<typename T>
    void ActionTarget<T>::unbind(const T& key)
    {
        auto remove_func = [&key](const std::pair<T,FuncType>& pair) -> bool
        {
            return pair.first == key;
        };

        const Action& action = _action_map.get(key);
        if(action._type & Action::Type::RealTime)
            _events_real_time.remove_if(remove_func);
        else
            _events_poll.remove_if(remove_func);
    }

}
