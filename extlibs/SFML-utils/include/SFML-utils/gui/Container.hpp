#ifndef SMFL_UTILS_GUI_CONTAINER_HPP
#define SMFL_UTILS_GUI_CONTAINER_HPP

#include <SFML-utils/gui/Widget.hpp>

namespace sfutils
{
    namespace gui
    {
        class Layout;
        class Container  : virtual public Widget
        {
            public:
                Container(const Container&) = delete;
                Container& operator=(const Container&) = delete;

                Container(Widget* parent=nullptr);
                virtual ~Container();
                
                void setLayout(Layout* layout);
                Layout* getLayout()const;

                void clear();

                void setFillColor(const sf::Color& color);
                void setOutlineColor(const sf::Color& color);
                void setOutlineThickness(float thickness);
                
                virtual sf::Vector2f getSize()const override;

            protected:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)override;
                virtual void processEvents(const sf::Vector2f& parent_pos)override;

                sf::RectangleShape _shape;

                virtual void updateShape()override;

            private:
                Layout* _layout;

        };
    }
}
#endif
