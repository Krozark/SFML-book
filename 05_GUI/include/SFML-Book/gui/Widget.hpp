#ifndef BOOK_GUI_WIDGET_HPP
#define BOOK_GUI_WIDGET_HPP

#include <SFML/Graphics.hpp>

namespace book
{
    namespace gui
    {
        class Layout;

        class Widget : public sf::Drawable
        {
            public:
                Widget(const Widget&) = delete;
                Widget& operator=(const Widget&) = delete;

                Widget(Layout* parent=nullptr);
                virtual ~Widget();

                void setPosition(const sf::Vector2f& pos);
                void setPosition(float x,float y);
                const sf::Vector2f& getPosition()const;

                virtual sf::Vector2f getSize()const = 0;

            protected:
                friend class Layout;
                friend class VLayout;

                virtual void processEvent(const sf::Event& event);
                virtual void processEvents();
                virtual void updateShape();

                sf::Vector2f getGlobalPosition()const;

                Layout* _parent;
                sf::Vector2f _position;
        };
    }
}
#endif
