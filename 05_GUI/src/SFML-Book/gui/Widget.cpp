#include <SFML-Book/gui/Widget.hpp>

#include <SFML-Book/gui/Layout.hpp>

namespace book
{
    namespace gui
    {
        Widget::Widget(Layout* parent) : _parent(parent)
        {
        }

        Widget::~Widget()
        {
        }

        void Widget::setPosition(const sf::Vector2f& pos)
        {
            _position = pos;
        }

        void Widget::setPosition(float x,float y)
        {
            _position.x = x;
            _position.y = y;
        }

        const sf::Vector2f& Widget::getPosition()const
        {
            return _position;
        }

        /*void Widget::setSize(const sf::Vector2f& size)
        {
            _size = size;
        }

        void Widget::setSize(float x,float y)
        {
            _size.x = x;
            _size.y = y;
        }

        const sf::Vector2f& Widget::getSize()const
        {
            return _size;
        }*/


        void Widget::processEvent(const sf::Event& event)
        {
        }

        void Widget::processEvents()
        {
        }

        sf::Vector2f Widget::getGlobalPosition()const
        {
            sf::Vector2f res = _position;
            if(_parent)
                res += _parent->getGlobalPosition();
            return res;
        }

    }
}
