#include <SFML-utils/gui/Frame.hpp>
#include <SFML-utils/gui/Layout.hpp>

#include <SFML-utils/gui/Configuration.hpp>

namespace sfutils
{
    namespace gui
    {
        Frame::Frame(sf::RenderWindow& window) : Frame(window,sfutils::gui::Configuration::default_gui_inputs)
        {
        }
        
        Frame::Frame(sf::RenderWindow& window,const ActionMap<int>& map) : Container(nullptr), ActionTarget(map), _window(window), _view(_window.getDefaultView())
        {
            ActionTarget::bind(Action(sf::Event::Resized),[this](const sf::Event& event){

                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                this->_view = sf::View(visibleArea);

                if(Layout* layout = getLayout())
                    layout->updateShape();
           });
        }

        Frame::~Frame()
        {
        }

        void Frame::draw()
        {
            _window.draw(*this);
        }

        void Frame::processEvents()
        {
            processEvents(sf::Vector2f(0,0));
        }

        bool Frame::processEvent(const sf::Event& event)
        {
            return processEvent(event,sf::Vector2f(0,0));
        }

        void Frame::bind(int key,const FuncType& callback)
        {
            ActionTarget::bind(key,callback);
        }

        void Frame::unbind(int key)
        {
            ActionTarget::unbind(key);
        }


        sf::Vector2f Frame::getSize()const
        {
            sf::Vector2f res = _size;
            sf::Vector2u wsize = _window.getSize();
            if(_size.x <= 0)
                res.x = wsize.x + _size.x;
            if(_size.y <= 0)
                res.y = wsize.y + _size.y;
            return res;
        }

        void Frame::setSize(const sf::Vector2f& size)
        {
            _size = size;
        }

        bool Frame::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)
        {
            bool res = false;
            if(_isVisible)
            {
                res = ActionTarget::processEvent(event);
                if(not res)
                    res = Container::processEvent(event,parent_pos);
            }
            return res;
        }

        void Frame::processEvents(const sf::Vector2f& parent_pos)
        {
            if(_isVisible)
            {
                ActionTarget::processEvents();
                Container::processEvents(parent_pos);
            }
        }

        void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(_isVisible)
            {
                sf::View view = target.getView();
                target.setView(_view);

                Container::draw(target,states);

                target.setView(view);
            }
        }
    }
}
