#include <SFML-Book/Action.hpp>

#include <cstring> //memcpy

namespace book
{
    Action::Action(const Action& other) : _type(other._type)
    {
        std::memcpy(&_event,&other._event,sizeof(sf::Event));
    }
    Action& Action::operator=(const Action& other)
    {
        std::memcpy(&_event,&other._event,sizeof(sf::Event));
        _type = other._type;
        return *this;
    }

    /*Action::Action(const sf::Event::EventType& event,int type) : _type(type)
    {
        _event.type = event;
    }*/

    Action::Action(const sf::Keyboard::Key& key,int type) : _type(type)
    {
        _event.type = sf::Event::EventType::KeyPressed;
        _event.key.code = key;
    }

    Action::Action(const sf::Mouse::Button& button,int type) : _type(type)
    {
        _event.type = sf::Event::EventType::MouseButtonPressed;
        std::memcpy(&_event.mouseButton,&button,sizeof(sf::Mouse::Button));
    }

    bool Action::operator==(const sf::Event& event)const
    {
        bool res = false;

        switch(event.type)
        {
            /*case sf::Event::EventType::TextEntered:
            {
                if(_event.type == sf::Event::EventType::TextEntered)
                    res = event.text.unicode == _event.text.unicode;
            }break;
            case sf::Event::EventType::MouseWheelMoved:
            {
                if(_event.type == sf::Event::EventType::MouseWheelMoved)
                    res = event.mouseWheel.delta == _event.mouseWheel.delta;
            }break;*/
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
            /*case sf::Event::EventType::JoystickButtonPressed:
            {
                if(_type & Type::Pressed and _event.type == sf::Event::EventType::JoystickButtonPressed)
                    res = event.joystickButton.button == _event.joystickButton.button;
            }break;
            case sf::Event::EventType::JoystickButtonReleased:
            {
                if(_type & Type::Releaseed and _event.type == sf::Event::EventType::JoystickButtonPressed)
                    res = event.joystickButton.button == _event.joystickButton.button;
            }break;*/
            default: break;
            /*{
                res = event.type == _event.type;
            }break;*/
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
        else if (_event.type == sf::Event::EventType::JoystickButtonPressed)
        {
            if(_type & Type::Pressed)
                res = sf::Joystick::isButtonPressed(0,_event.joystickButton.button);
        }
        return res;
    }
}
