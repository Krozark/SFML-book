#include <SFML-Book/Piece.hpp>

#include <SFML-Book/converter.hpp>

#include <iostream>


namespace book
{
    const sf::Color Piece::Tetrimino_colors[Piece::Tetrimino_Types::SIZE]= {
        sf::Color::Blue,
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Cyan,
        sf::Color::Magenta,
        sf::Color::White,
        sf::Color(195,132,58)
    };
    
    Piece::Piece(b2World& world,int pos_x,int pos_y,Tetrimino_Types type,float rotation) : _world(world)
    {
        b2BodyDef bodyDef;

        bodyDef.position.Set(book::converter::pixel_to_meters<double>(pos_x),book::converter::pixel_to_meters<double>(pos_y));
        bodyDef.type = b2_dynamicBody;
        bodyDef.angle = converter::deg_to_rad(rotation);

        _body = world.CreateBody(&bodyDef);

        switch(type)
        {
            case Tetrimino_Types::O :
            {
                create_part(0,0,type);
                create_part(0,1,type);
                create_part(1,0,type);
                create_part(1,1,type);
            }break;
            case Tetrimino_Types::I :
            {
                create_part(0,0,type);
                create_part(1,0,type);
                create_part(2,0,type);
                create_part(3,0,type);
            }break;
            case Tetrimino_Types::S :
            {
                create_part(0,1,type);
                create_part(1,1,type);
                create_part(1,0,type);
                create_part(2,0,type);
            }break;
            case Tetrimino_Types::Z :
            {
                create_part(0,0,type);
                create_part(1,0,type);
                create_part(1,1,type);
                create_part(2,1,type);
            }break;
            case Tetrimino_Types::L :
            {
                create_part(0,1,type);
                create_part(0,0,type);
                create_part(1,0,type);
                create_part(2,0,type);
            }break;
            case Tetrimino_Types::J :
            {
                create_part(0,0,type);
                create_part(1,0,type);
                create_part(2,0,type);
                create_part(2,1,type);
            }break;
            case Tetrimino_Types::T :
            {
                create_part(0,0,type);
                create_part(1,0,type);
                create_part(1,1,type);
                create_part(2,0,type);
            }break;
            default:break;
        }

        _body->SetUserData(this);
        update();
    }

    Piece::~Piece()
    {
        //destroy shapes
        for(b2Fixture* fixture=_body->GetFixtureList();fixture!=nullptr;fixture=fixture->GetNext())
        {
            sf::ConvexShape* shape = static_cast<sf::ConvexShape*>(fixture->GetUserData());
            fixture->SetUserData(nullptr);
            delete shape;
        }
        _world.DestroyBody(_body);
    }

    b2Fixture* Piece::create_part(int pos_x,int pos_y,Tetrimino_Types type)
    {
        b2PolygonShape b2shape;
        

        b2shape.SetAsBox(converter::pixel_to_meters<double>(BOOK_BOX_SIZE_2),converter::pixel_to_meters<double>(BOOK_BOX_SIZE_2)
                         ,b2Vec2(converter::pixel_to_meters<double>(BOOK_BOX_SIZE_2+(pos_x*BOOK_BOX_SIZE)),converter::pixel_to_meters<double>(BOOK_BOX_SIZE_2+(pos_y*BOOK_BOX_SIZE))),0);

        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.5;
        fixtureDef.restitution= 0.4;
        fixtureDef.shape = &b2shape;

        b2Fixture* fixture = _body->CreateFixture(&fixtureDef);

        sf::ConvexShape* shape = new sf::ConvexShape((unsigned int)b2shape.GetVertexCount());
        shape->setFillColor(Tetrimino_colors[type]);
        shape->setOutlineThickness(1.0f);
        shape->setOutlineColor(sf::Color(128,128,128));

        fixture->SetUserData(shape);

        return fixture;
    }

    void Piece::update()
    {
        const b2Transform& xf = _body->GetTransform();

        for(b2Fixture* fixture = _body->GetFixtureList(); fixture != nullptr;fixture=fixture->GetNext())
        {
            sf::ConvexShape* shape = static_cast<sf::ConvexShape*>(fixture->GetUserData());

            const b2PolygonShape* b2shape = static_cast<b2PolygonShape*>(fixture->GetShape());
            const uint32 count = b2shape->GetVertexCount();
            for(uint32 i=0;i<count;++i)
            {
                b2Vec2 vertex = b2Mul(xf,b2shape->m_vertices[i]);
                shape->setPoint(i,sf::Vector2f(converter::meters_to_pixels(vertex.x),
                                                converter::meters_to_pixels(vertex.y)));
            }
        } 
    }

    void Piece::rotate(float angle)
    {
        _body->ApplyTorque((float32)converter::deg_to_rad(angle),true);
    }

    void Piece::moveX(int direction)
    {
        _body->ApplyForceToCenter(b2Vec2(converter::pixel_to_meters(direction),0),true);
    }

    b2Body* Piece::getBody()const
    {
        return _body;
    }

    void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(const b2Fixture* fixture=_body->GetFixtureList();fixture!=nullptr;fixture=fixture->GetNext())
        {
            sf::ConvexShape* shape = static_cast<sf::ConvexShape*>(fixture->GetUserData());
            if(shape)
                target.draw(*shape,states);
        }
    }
}
