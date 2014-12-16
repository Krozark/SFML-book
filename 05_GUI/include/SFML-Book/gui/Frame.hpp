#ifndef BOOK_GUI_FRAME_HPP
#define BOOK_GUI_FRAME_HPP

#include <SFML-Book/gui/Widget.hpp>
#include <SFML-Book/ActionTarget.hpp>

namespace book
{
    namespace gui
    {
        class Layout;
        class Frame : public Widget, protected ActionTarget<int>
        {
            public:
                Frame(const Frame&) = delete;
                Frame& operator=(const Frame&) = delete;

                using ActionTarget<int>::FuncType;
                
                Frame(sf::RenderWindow& window);
                Frame(sf::RenderWindow& window,float size_x,float size_y);

                virtual ~Frame();

                void setLayout(Layout* layout);
                Layout* getLayout()const;

                void processEvents();
                bool processEvent(const sf::Event& event);

                void bind(int key,const FuncType& callback);
                void unbind(int key);



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
