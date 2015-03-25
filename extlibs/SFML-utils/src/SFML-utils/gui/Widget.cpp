#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        Widget::Widget(Widget* parent) : _parent(parent), _isVisible(true)
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

        void Widget::hide()
        {
            if(_isVisible == true)
            {
                _isVisible = false;
                updateShape();
            }
        }

        void Widget::show()
        {
            if(_isVisible == false)
            {
                _isVisible = true;
                updateShape();
            }
        }

        bool Widget::isHidden()const
        {
            return not _isVisible;
        }

        bool Widget::isVisible()const
        {
            return _isVisible;
        }

        void Widget::toggle()
        {
            _isVisible = not _isVisible;
            updateShape();
        }


        bool Widget::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)
        {
            return false;
        }

        void Widget::processEvents(const sf::Vector2f& parent_pos)
        {
        }

        void Widget::updateShape()
        {
            if(_parent)
                _parent->updateShape();
        }
    }
}
