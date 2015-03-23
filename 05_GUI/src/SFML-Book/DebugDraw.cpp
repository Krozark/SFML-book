#include <SFML-Book/DebugDraw.hpp>
#include <SFML-Book/converter.hpp>

namespace book
{
    DebugDraw::DebugDraw() : _render(sf::VideoMode(800,900),"Debug Draw")
    {
        uint32 flags = b2Draw::e_shapeBit;
        //flags += b2Draw::e_jointBit;
        flags += b2Draw::e_aabbBit;
        //flags += b2Draw::e_pairBit;
        //flags += b2Draw::e_centerOfMassBit;
        SetFlags(flags);
    }

    void DebugDraw::DrawPolygon(const b2Vec2* vertices,int32 vertexCount,const b2Color& color)
    {
        sf::ConvexShape polygon((unsigned int)vertexCount);
        for (int32 i=0; i<vertexCount;++i)
        {
            const b2Vec2& vertex = vertices[i];
            polygon.setPoint(i,sf::Vector2f(converter::metersToPixels(vertex.x),
                             converter::metersToPixels(vertex.y)));
        }
        polygon.setFillColor(sf::Color::Transparent);
        polygon.setOutlineThickness(-1.0f);
        polygon.setOutlineColor(_b2ToSf(color,50));
        _render.draw(polygon);
    }

    void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices,int32 vertexCount,const b2Color& color)
    {
        sf::ConvexShape polygon((unsigned int)vertexCount);
        for (int32 i=0; i<vertexCount;++i)
        {
            const b2Vec2& vertex = vertices[i];
            polygon.setPoint(i,sf::Vector2f(converter::metersToPixels(vertex.x),
                             converter::metersToPixels(vertex.y)));
        }
        polygon.setFillColor(_b2ToSf(color,50));
        polygon.setOutlineThickness(1.0f);
        polygon.setOutlineColor(_b2ToSf(color));
        _render.draw(polygon);
    }

    void DebugDraw::DrawCircle(const b2Vec2& center,float32 radius,const b2Color& color)
    {
        sf::CircleShape circle(converter::metersToPixels(radius),30);
        circle.setOrigin(converter::metersToPixels(radius),converter::metersToPixels(radius));
        circle.setPosition(converter::metersToPixels(center.x),converter::metersToPixels(center.y));

        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(-1.0f);
        circle.setOutlineColor(_b2ToSf(color));
        _render.draw(circle);
    }

    void DebugDraw::DrawSolidCircle(const b2Vec2& center,float32 radius,const b2Vec2& axis,const b2Color& color)
    {
        sf::CircleShape circle(converter::metersToPixels(radius),30);
        circle.setOrigin(converter::metersToPixels(radius),converter::metersToPixels(radius));
        circle.setPosition(converter::metersToPixels(center.x),converter::metersToPixels(center.y));

        circle.setFillColor(_b2ToSf(color,50));
        circle.setOutlineThickness(1.0f);
        circle.setOutlineColor(_b2ToSf(color));
        _render.draw(circle);

         b2Vec2 p = center + (radius * axis);
         DrawSegment(center,p,color);
    }

    void DebugDraw::DrawSegment(const b2Vec2& p1,const b2Vec2& p2,const b2Color& color)
    {
        sf::VertexArray line(sf::Lines,2);
        line[0] = sf::Vertex(sf::Vector2f(converter::metersToPixels(p1.x),converter::metersToPixels(p1.y)),_b2ToSf(color));
        line[1] = sf::Vertex(sf::Vector2f(converter::metersToPixels(p2.x),converter::metersToPixels(p2.y)),_b2ToSf(color));
        _render.draw(line);
    }

    void DebugDraw::DrawTransform(const b2Transform &xf)
    {
        const float lineLength = 0.4;

        b2Vec2 p = xf.p + lineLength*xf.q.GetYAxis();

        sf::VertexArray line(sf::Lines,2);
        line[0] = sf::Vertex(sf::Vector2f(converter::metersToPixels(xf.p.x),converter::metersToPixels(xf.p.y)),sf::Color::Red);
        line[1] = sf::Vertex(sf::Vector2f(converter::metersToPixels(p.x),converter::metersToPixels(p.y)),sf::Color::Red);
        _render.draw(line);

        p = xf.p + lineLength * xf.q.GetYAxis();
        line[0] = sf::Vertex(sf::Vector2f(converter::metersToPixels(xf.p.x),converter::metersToPixels(xf.p.y)),sf::Color::Green);
        line[1] = sf::Vertex(sf::Vector2f(converter::metersToPixels(p.x),converter::metersToPixels(p.y)),sf::Color::Green);
        _render.draw(line);
    }

    void DebugDraw::clear()
    {
        _render.clear();
    }

    void DebugDraw::display()
    {
        _render.display();
    }

    sf::Color DebugDraw::_b2ToSf(const b2Color& color,int alpha)const
    {
        return sf::Color((sf::Uint8)(color.r*255),
                         (sf::Uint8)(color.g*255),
                         (sf::Uint8)(color.b*255),
                         (sf::Uint8)alpha);
    }
}
