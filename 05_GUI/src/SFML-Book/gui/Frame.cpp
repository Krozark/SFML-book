#include <SFML-Book/gui/Frame.hpp>

#include <SFML-Book/gui/Layout.hpp>

namespace book
{
    namespace gui
    {
        Frame::Frame(sf::RenderWindow& window,float size_x,float size_y) : Widget(nullptr), _layout(nullptr), _window(window)
        {
        }

        Frame::Frame(sf::RenderWindow& window) : Frame(window,window.getSize().x,window.getSize().y)
        {
        }

        Frame::~Frame()
        {
            if(_layout != nullptr and _layout->_parent == this)
            {
                _layout->_parent = nullptr;
                delete _layout;
            }
        }

        void Frame::setLayout(Layout* layout)
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

        Layout* Frame::getLayout()const
        {
            return _layout;
        }

        void Frame::draw()
        {
            _window.draw(*this);
        }

        void Frame::processEvents()
        {
            sf::Vector2f parent_pos(0,0);
            processEvents(parent_pos);
        }

        void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(_layout)
                target.draw(
                            *_layout,
                            states.transform.translate(_position)
                );
        }

        sf::Vector2f Frame::getSize()const
        {
            sf::Vector2u size = _window.getSize();
            return sf::Vector2f(size.x,size.y);
        }

        bool Frame::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)
        {
            bool res = false;
            const sf::Vector2f pos = _position + parent_pos;
            if(_layout)
                res = _layout->processEvent(event,pos);
            return res;
        }

        void Frame::processEvents(const sf::Vector2f& parent_pos)
        {
            const sf::Vector2f pos = _position + parent_pos;
            if(_layout)
            {
                _layout->processEvents(pos);
                sf::Event event;
                while(_window.pollEvent(event))
                    _layout->processEvent(event,pos);
            }
        }


    }
}
