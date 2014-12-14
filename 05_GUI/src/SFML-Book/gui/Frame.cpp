#include <SFML-Book/gui/Frame.hpp>
#include <SFML-Book/gui/Layout.hpp>

namespace book
{
    namespace gui
    {
        
        Frame::Frame(sf::RenderWindow& window,float size_x,float size_y) : Widget(nullptr), _layout(nullptr), _window(window), _size(size_x,size_y)
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
            if(_layout)
            {
                _layout->processEvents();
                sf::Event event;
                while(_window.pollEvent(event))
                    _layout->processEvent(event);
            }
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
            return _size;
        }

        
        void Frame::processEvent(const sf::Event& event)
        {
            if(_layout)
                _layout->processEvent(event);
        }

    }
}
