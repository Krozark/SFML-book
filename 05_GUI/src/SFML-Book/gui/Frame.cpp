#include <SFML-Book/gui/Frame.hpp>

#include <SFML-Book/gui/Layout.hpp>
#include <SFML-Book/Configuration.hpp>

namespace book
{
    namespace gui
    {
        Frame::Frame(sf::RenderWindow& window,float size_x,float size_y) : Widget(nullptr), ActionTarget(Configuration::gui_inputs),_layout(nullptr), _window(window)
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

        bool Frame::processEvent(const sf::Event& event)
        {
            sf::Vector2f parent_pos(0,0);
            return processEvent(event,parent_pos);
        }

        void Frame::bind(int key,const FuncType& callback)
        {
            ActionTarget::bind(key,callback);
        }

        void Frame::unbind(int key)
        {
            ActionTarget::unbind(key);
        }

        void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(_layout)
                target.draw(*_layout,states);
        }

        sf::Vector2f Frame::getSize()const
        {
            sf::Vector2u size = _window.getSize();
            return sf::Vector2f(size.x,size.y);
        }

        bool Frame::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)
        {
            bool res = ActionTarget::processEvent(event);
            if(not res and _layout)
                res = _layout->processEvent(event,parent_pos);
            return res;
        }

        void Frame::processEvents(const sf::Vector2f& parent_pos)
        {
            ActionTarget::processEvents();
            if(_layout)
            {
                _layout->processEvents(parent_pos);
                sf::Event event;
                while(_window.pollEvent(event))
                    _layout->processEvent(event,parent_pos);
            }
        }


    }
}
