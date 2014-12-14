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

        void Widget::processEvent(const sf::Event& event)
        {
        }

        void Widget::processEvents()
        {
        }

        void Widget::updateShape()
        {
            if(_parent)
                _parent->updateShape();
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
