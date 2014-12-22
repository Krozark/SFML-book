#ifndef BOOK_GUI_VLAYOUT_HPP
#define BOOK_GUI_VLAYOUT_HPP

#include <SFML-Book/gui/Layout.hpp>
#include <vector>

namespace book
{
    namespace gui
    {
        class VLayout : public Layout
        {
            public:
                VLayout(const VLayout&) = delete;
                VLayout& operator=(const VLayout&) = delete;

                VLayout(Widget* parent = nullptr);
                ~VLayout();

                void add(Widget* widget);
                Widget* at(unsigned int index)const;

                virtual sf::Vector2f getSize()const override;

            protected:
                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos) override;
                virtual void processEvents(const sf::Vector2f& parent_pos) override;

            private:
                std::vector<Widget*> _widgets;

                virtual void updateShape() override;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}
#endif
