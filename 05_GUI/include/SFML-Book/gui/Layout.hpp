#ifndef BOOK_GUI_LAYOUT_HPP
#define BOOK_GUI_LAYOUT_HPP

#include <SFML/Graphics.hpp>

#include <SFML-Book/gui/Widget.hpp>

namespace book
{
    namespace gui
    {
        class Layout : protected Widget /*public sf::Drawable*/
        {
            public:
                Layout(const Layout&) = delete;
                Layout& operator=(const Layout&) = delete;

                Layout(Widget* parent=nullptr);
                virtual ~Layout();

                virtual sf::Vector2f getSize()const = 0;

                void setSpace(float pixels);

            protected:
                friend class Frame;
                friend class Widget;

                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos) = 0;
                virtual void processEvents(const sf::Vector2f& parent_pos) = 0;
                virtual void updateShape() = 0;

                float _space;
        };
    }
}
#endif
