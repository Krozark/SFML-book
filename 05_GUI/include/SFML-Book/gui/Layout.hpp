#ifndef BOOK_GUI_LAYOUT_HPP
#define BOOK_GUI_LAYOUT_HPP

#include <SFML/Graphics.hpp>

#include <SFML-Book/gui/Widget.hpp>

namespace book
{
    namespace gui
    {
        class Layout : protected Widget
        {
            public:
                Layout(const Layout&) = delete;
                Layout& operator=(const Layout&) = delete;

                Layout(Widget* parent=nullptr);
                virtual ~Layout();

                void setSpace(float pixels);

            protected:
                friend class Container;

                float _space;
        };
    }
}
#endif
