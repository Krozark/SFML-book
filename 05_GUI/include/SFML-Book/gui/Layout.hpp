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

                float _space;
        };
    }
}
#endif
