#ifndef BOOK_GUI_WIDGET_HPP
#define BOOK_GUI_WIDGET_HPP

namespace book
{
    namespace gui
    {
        class Widget
        {
            public:
                Widget();
                Widget(const Widget&) = delete;
                Widget& operator=(const Widget&) = delete;

            private:
        };
    }
}
#endif
