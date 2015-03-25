#include <SFML-utils/gui/VLayout.hpp>

#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        VLayout::VLayout(Widget* parent) : Layout(parent)
        {
        }

        VLayout::~VLayout()
        {
            clear();
        }

        void VLayout::add(Widget* widget)
        {
            widget->_parent = this;
            _widgets.emplace_back(widget);
            updateShape();
        }

        Widget* VLayout::at(unsigned int index)const
        {
            return _widgets.at(index);
        }

        sf::Vector2f VLayout::getSize()const
        {
            float max_x = 0;
            float y = 0;
            for(Widget* widget : _widgets)
            {
                if(widget->_isVisible)
                {
                    sf::Vector2f size = widget->getSize();
                    if(size.x > max_x)
                        max_x = size.x;
                    y+= _spacing + size.y;
                }
            }
            return sf::Vector2f(max_x + _spacing*2,y + _spacing);
        }

        void VLayout::clear()
        {
            for(Widget* widget : _widgets)
            {
                if(widget->_parent == this)
                    delete widget;
            }
            _widgets.clear();
            updateShape();
        }

        bool VLayout::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)
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

        void VLayout::processEvents(const sf::Vector2f& parent_pos)
        {
            if(_isVisible)
            {
                for(Widget* widget : _widgets)
                    if(widget->_isVisible)
                        widget->processEvents(parent_pos);
            }
        }

        void VLayout::updateShape()
        {
            float max_x = (_parent?_parent->getSize().x:0);
            for(Widget* widget : _widgets)
            {
                if(widget->_isVisible)
                {
                    sf::Vector2f size = widget->getSize();
                    float widget_x = size.x;

                    if(widget_x > max_x)
                        max_x = widget_x;
                }
            }

            float pos_y = _spacing;
            if(_parent)
                pos_y = (_parent->getSize().y - getSize().y)/2.f;

            for(Widget* widget : _widgets)
            {
                if(widget->_isVisible)
                {
                    sf::Vector2f size = widget->getSize();
                    widget->setPosition((max_x-size.x)/2.0,pos_y);
                    pos_y += size.y + _spacing;
                }
            }
            Widget::updateShape();
        }

        void VLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
