#include <SFML-Book/ActionTarget.hpp>

namespace book
{
    ActionTarget::ActionTarget()
    {
    }

    bool ActionTarget::processEvent(const sf::Event& event)const
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

    void ActionTarget::processEvents()const
    {
        for(auto& action : _events_real_time)
        {
            if(action.first.test())
                action.second(action.first._event);
        }
    }

    void ActionTarget::bind(const book::Action& action,const FuncType& callback)
    {
        if(action._type & Action::Type::RealTime)
            _events_real_time.emplace_back(action,callback);
        else
            _events_poll.emplace_back(action,callback);

    }

    void ActionTarget::unbind(const book::Action& action)
    {
        auto remove_func = [&action](const std::pair<book::Action,FuncType>& pair) -> bool
        {
            return pair.first == action;
        };

        if(action._type & Action::Type::RealTime)
            _events_real_time.remove_if(remove_func);
        else
            _events_poll.remove_if(remove_func);
    }

}
