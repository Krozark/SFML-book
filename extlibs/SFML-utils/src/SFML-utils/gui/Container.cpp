#include <SFML-utils/gui/Container.hpp>

#include <SFML-utils/gui/Layout.hpp>

namespace sfutils
{
    namespace gui
    {
        Container::Container(Widget* parent) : Widget(parent), _layout(nullptr)
        {
            setFillColor(sf::Color(255,255,255,0));
            setOutlineColor(sf::Color(255,255,255,0));
            setOutlineThickness(0);
        }

        Container::~Container()
        {
            if(_layout != nullptr and _layout->_parent == this)
            {
                _layout->_parent = nullptr;
                delete _layout;
            }
        }

        void Container::setLayout(Layout* layout)
        {
            if(_layout != nullptr and _layout->_parent == this)
            {
                _layout->_parent = nullptr;
                delete _layout;
            }

            if((_layout = layout) != nullptr)
            {
                _layout->_parent = this;
                _layout->updateShape();
            }
        }

        Layout* Container::getLayout()const
        {
            return _layout;
        }

        void Container::clear()
        {
            if(_layout)
            {
                _layout->clear();
                updateShape();
            }
        }

        void Container::setFillColor(const sf::Color& color)
        {
            _shape.setFillColor(color);
        }

        void Container::setOutlineColor(const sf::Color& color)
        {
            _shape.setOutlineColor(color);
        }

        void Container::setOutlineThickness(float thickness)
        {
            _shape.setOutlineThickness(thickness);
        }

        sf::Vector2f Container::getSize()const
        {
            sf::Vector2f res(0,0);
            if(_layout)
                res = _layout->getSize();
            return res;
        }
        
        void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(_isVisible and _layout)
            {
                states.transform.translate(_position);
                target.draw(_shape,states);
                target.draw(*_layout,states);
            }
        }

        bool Container::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)
        {
            bool res = false;
            if(_isVisible and _layout)
                res = _layout->processEvent(event,_position + parent_pos);
            return res;
        }

        void Container::processEvents(const sf::Vector2f& parent_pos)
        {
            if(_isVisible and _layout)
                _layout->processEvents(_position + parent_pos);
        }

        void Container::updateShape()
        {
            _shape.setSize(getSize());
            Widget::updateShape();
        }
    }
}
