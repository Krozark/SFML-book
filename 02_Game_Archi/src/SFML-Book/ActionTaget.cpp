#include <SFML-Book/ActionTaget.hpp>

namespace book
{
    ActionTaget::ActionTaget()
    {
    }

    bool ActionTaget::processEvent(const sf::Event& event)const
    {
        bool res = false;
        for(auto& action : _events_poll)
        {
            if(action.first == event)
            {
                action.second(event);
                res = true;
                break;
            }
        }
        return res;
    }

    void ActionTaget::processEvents()const
    {
        for(auto& action : _events_real_time)
        {
            if(action.first.test())
                action.second(action.first._event);
        }
    }

    void ActionTaget::bind(const book::Action& action,const std::function<void(const sf::Event&)>& callback)
    {
        if(action._type & Action::Type::RealTime)
            _events_real_time.emplace_back(action,callback);
        else
            _events_poll.emplace_back(action,callback);

    }

    void ActionTaget::unbind(const book::Action& action)
    {
        auto remove_func = [&action](const std::pair<book::Action,std::function<void(const sf::Event&)>>& pair) -> bool
        {
            return pair.first == action;
        };
        if(action._type & Action::Type::RealTime)
        {
            _events_real_time.remove_if(remove_func);
        }
        else
        {
            _events_poll.remove_if(remove_func);
        }
    }

}
