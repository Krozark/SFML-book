#include <SFML-utils/box2D/DebugDraw.hpp>
#include <SFML-utils/box2D/converter.hpp>

namespace sfutils
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
            polygon.setPoint(i,sf::Vector2f(converter::meters_to_pixels(vertex.x),
                             converter::meters_to_pixels(vertex.y)));
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
            polygon.setPoint(i,sf::Vector2f(converter::meters_to_pixels(vertex.x),
                             converter::meters_to_pixels(vertex.y)));
        }
        polygon.setFillColor(_b2ToSf(color,50));
        polygon.setOutlineThickness(1.0f);
        polygon.setOutlineColor(_b2ToSf(color));
        _render.draw(polygon);
    }

    void DebugDraw::DrawCircle(const b2Vec2& center,float32 radius,const b2Color& color)
    {
        sf::CircleShape circle(converter::meters_to_pixels(radius),30);
        circle.setOrigin(converter::meters_to_pixels(radius),converter::meters_to_pixels(radius));
        circle.setPosition(converter::meters_to_pixels(center.x),converter::meters_to_pixels(center.y));

        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(-1.0f);
        circle.setOutlineColor(_b2ToSf(color));
        _render.draw(circle);
    }

    void DebugDraw::DrawSolidCircle(const b2Vec2& center,float32 radius,const b2Vec2& axis,const b2Color& color)
    {
        sf::CircleShape circle(converter::meters_to_pixels(radius),30);
        circle.setOrigin(converter::meters_to_pixels(radius),converter::meters_to_pixels(radius));
        circle.setPosition(converter::meters_to_pixels(center.x),converter::meters_to_pixels(center.y));

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
        line[0] = sf::Vertex(sf::Vector2f(converter::meters_to_pixels(p1.x),converter::meters_to_pixels(p1.y)),_b2ToSf(color));
        line[1] = sf::Vertex(sf::Vector2f(converter::meters_to_pixels(p2.x),converter::meters_to_pixels(p2.y)),_b2ToSf(color));
        _render.draw(line);
    }

    void DebugDraw::DrawTransform(const b2Transform &xf)
    {
        const float lineLength = 0.4;

        b2Vec2 p = xf.p + lineLength*xf.q.GetYAxis();

        sf::VertexArray line(sf::Lines,2);
        line[0] = sf::Vertex(sf::Vector2f(converter::meters_to_pixels(xf.p.x),converter::meters_to_pixels(xf.p.y)),sf::Color::Red);
        line[1] = sf::Vertex(sf::Vector2f(converter::meters_to_pixels(p.x),converter::meters_to_pixels(p.y)),sf::Color::Red);
        _render.draw(line);

        p = xf.p + lineLength * xf.q.GetYAxis();
        line[0] = sf::Vertex(sf::Vector2f(converter::meters_to_pixels(xf.p.x),converter::meters_to_pixels(xf.p.y)),sf::Color::Green);
        line[1] = sf::Vertex(sf::Vector2f(converter::meters_to_pixels(p.x),converter::meters_to_pixels(p.y)),sf::Color::Green);
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
