#include <SFML-Book/Action.hpp>

namespace book
{
    Action::Action(const sf::Keyboard::Key& key,int type) : _type(type)
    {
        _event.type = sf::Event::EventType::KeyPressed;
        _event.key.code = key;
    }

    Action::Action(const sf::Mouse::Button& button,int type) : _type(type)
    {
        _event.type = sf::Event::EventType::MouseButtonPressed;
        _event.mouseButton.button = button;
    }

    bool Action::operator==(const sf::Event& event)const
    {
        bool res = false;

        switch(event.type)
        {
            case sf::Event::EventType::KeyPressed:
            {
                if(_type & Type::Pressed and _event.type == sf::Event::EventType::KeyPressed)
                    res = event.key.code == _event.key.code;
            }break;
            case sf::Event::EventType::KeyReleased:
            {
                if(_type & Type::Released and _event.type == sf::Event::EventType::KeyPressed)
                    res = event.key.code == _event.key.code;
            }break;
            case sf::Event::EventType::MouseButtonPressed:
            {
                if(_type & Type::Pressed and _event.type == sf::Event::EventType::MouseButtonPressed)
                    res = event.mouseButton.button == _event.mouseButton.button;
            }break;
            case sf::Event::EventType::MouseButtonReleased:
            {
                if(_type & Type::Released and _event.type == sf::Event::EventType::MouseButtonPressed)
                    res = event.mouseButton.button == _event.mouseButton.button;
            }break;
            default: break;
        }
        return res;
    }

    bool Action::operator==(const Action& other)const
    {
        return _type == other._type and other == _event;
    }

    bool Action::test()const
    {
        bool res = false;
        if(_event.type == sf::Event::EventType::KeyPressed)
        {
            if(_type & Type::Pressed)
                res = sf::Keyboard::isKeyPressed(_event.key.code);
        }
        else if (_event.type == sf::Event::EventType::MouseButtonPressed)
        {
            if(_type & Type::Pressed)
                res = sf::Mouse::isButtonPressed(_event.mouseButton.button);
        }
        return res;
    }
}
