#ifndef SFML_UTILS_DEBUGDRAW_HPP
#define SFML_UTILS_DEBUGDRAW_HPP

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace sfutils
{
    class DebugDraw : public b2Draw
    {
        public:
            DebugDraw();
            virtual ~DebugDraw() = default;

            DebugDraw(const DebugDraw&) = delete;
            DebugDraw& operator=(const DebugDraw&) = delete;

            virtual void DrawPolygon(const b2Vec2* vertices,int32 vertexCount,const b2Color& color);
            virtual void DrawSolidPolygon(const b2Vec2* vertices,int32 vertexCount,const b2Color& color);
            virtual void DrawCircle(const b2Vec2 &center,float32 radius,const b2Color& color);
            virtual void DrawSolidCircle(const b2Vec2& center,float32 radius, const b2Vec2& axis,const b2Color& color);
            virtual void DrawSegment(const b2Vec2& p1,const b2Vec2& p2, const b2Color& color);
            virtual void DrawTransform(const b2Transform& xf);

            void clear();
            void display();

        private:
            

            sf::Color _b2ToSf(const b2Color& color,int alpha=255)const;
            sf::RenderWindow _render;
    };
}
#endif
