#ifndef BOOK_GUI_LAYOUT_HPP
#define BOOK_GUI_LAYOUT_HPP

#include <SFML/Graphics.hpp>

namespace book
{
    namespace gui
    {
        class Widget;
        class Layout : public sf::Drawable
        {
            public:
                Layout(const Layout&) = delete;
                Layout& operator=(const Layout&) = delete;

                Layout(Widget* parent=nullptr);
                virtual ~Layout();

                virtual sf::Vector2f getSize()const = 0;

            protected:
                friend class Frame;
                friend class Widget;

                Widget* _parent;

                virtual void processEvent(const sf::Event& event) = 0;
                virtual void processEvents() = 0;
                virtual void updateShape() = 0;

                sf::Vector2f getGlobalPosition()const;

        };
    }
}
#endif
