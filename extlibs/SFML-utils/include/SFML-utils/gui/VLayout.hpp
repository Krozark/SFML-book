#ifndef SMFL_UTILS_GUI_VLAYOUT_HPP
#define SMFL_UTILS_GUI_VLAYOUT_HPP

#include <SFML-utils/gui/Layout.hpp>
#include <vector>

namespace sfutils
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

                virtual void clear();

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
