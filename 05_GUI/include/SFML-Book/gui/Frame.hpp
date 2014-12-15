#ifndef BOOK_GUI_FRAME_HPP
#define BOOK_GUI_FRAME_HPP

#include <SFML-Book/gui/Widget.hpp>

namespace book
{
    namespace gui
    {
        class Layout;
        class Frame : private Widget
        {
            public:
                Frame(const Frame&) = delete;
                Frame& operator=(const Frame&) = delete;
                
                Frame(sf::RenderWindow& window);
                Frame(sf::RenderWindow& window,float size_x,float size_y);

                virtual ~Frame();

                void setLayout(Layout* layout);
                Layout* getLayout()const;

                void processEvents();

                void draw();

                virtual sf::Vector2f getSize()const override;


            private:
                Layout* _layout;
                sf::RenderWindow& _window;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

                virtual bool processEvent(const sf::Event& event,const sf::Vector2f& parent_pos)override;
                virtual void processEvents(const sf::Vector2f& parent_pos)override;
        };
    }
}
#endif
