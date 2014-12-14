#ifndef BOOK_GUI_FRAME_HPP
#define BOOK_GUI_FRAME_HPP

#include <SFML-Book/gui/Widget.hpp>

namespace book
{
    namespace gui
    {
        class Frame : public Widget
        {
            public:
                Frame(const Frame&) = delete;
                Frame& operator=(const Frame&) = delete;
                
                Frame(sf::RenderWindow& window);
                Frame(sf::RenderWindow& window,float size_x,float size_y);

                virtual ~Frame();

                void setLayout(Layout* layout);
                Layout* getLayout()const;

                void draw();
                virtual void processEvents()override;

                virtual sf::Vector2f getSize()const override;


            private:
                Layout* _layout;
                sf::RenderWindow& _window;

                sf::Vector2f _size;

                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

                virtual void processEvent(const sf::Event& event)override;
        };
    }
}
#endif
