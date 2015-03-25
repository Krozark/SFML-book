#include <SFML-utils/gui/HLayout.hpp>

#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        HLayout::HLayout(Widget* parent) : Layout(parent)
        {
        }

        HLayout::~HLayout()
        {
            clear();
        }

        void HLayout::add(Widget* widget)
        {
            widget->_parent = this;
            _widgets.emplace_back(widget);
            updateShape();
        }

        Widget* HLayout::at(unsigned int index)const
        {
            return _widgets.at(index);
        }


        sf::Vector2f HLayout::getSize()const
        {
            float max_y = 0;
            float x = 0;
            for(Widget* widget : _widgets)
            {
                if(widget->_isVisible)
                {
                    sf::Vector2f size = widget->getSize();
                    if(size.y > max_y)
                        max_y = size.y;
                    x+= _spacing + size.x;
                }
            }
            return sf::Vector2f(x + _spacing, max_y + _spacing*2);
        }

        void HLayout::clear()
        {
            for(Widget* widget : _widgets)
            {
                if(widget->_parent == this)
                    delete widget;
            }
            _widgets.clear();
            updateShape();
        }

        bool HLayout::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)
        {
            if(_isVisible)
            {
                for(Widget* widget : _widgets)
                {
                    if(widget->_isVisible and widget->processEvent(event,parent_pos))
                        return true;
                }
            }
            return false;
        }

        void HLayout::processEvents(const sf::Vector2f& parent_pos)
        {
            if(_isVisible)
            {
                for(Widget* widget : _widgets)
                    if(widget->_isVisible)
                        widget->processEvents(parent_pos);
            }
        }

        void HLayout::updateShape()
        {
            float max_y = (_parent?_parent->getSize().y:0);
            for(Widget* widget : _widgets)
            {
                if(widget->_isVisible)
                {
                    sf::Vector2f size = widget->getSize();
                    float widget_y = size.y;

                    if(widget_y > max_y)
                        max_y = widget_y;
                }
            }

            float pos_x = _spacing;
            if(_parent)
                pos_x = (_parent->getSize().x - getSize().x)/2.f;

            for(Widget* widget : _widgets)
            {
                if(widget->_isVisible)
                {
                    sf::Vector2f size = widget->getSize();
                    widget->setPosition(pos_x,(max_y-size.y)/2.0);
                    pos_x += size.x + _spacing;
                }
            }
            Widget::updateShape();
        }

        void HLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(_isVisible)
            {
                for(Widget* widget : _widgets)
                    if(widget->_isVisible)
                        target.draw(*widget,states);
            }
        }


    }
}
