#include <SFML-Book/Piece.hpp>

#include <SFML-Book/converter.hpp>


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
                create_part(0,0,rotation,type);
                create_part(0,1,rotation,type);
                create_part(1,0,rotation,type);
                create_part(1,1,rotation,type);
            }break;
            case Tetrimino_Types::I :
            {
                create_part(0,0,rotation,type);
                create_part(1,0,rotation,type);
                create_part(2,0,rotation,type);
                create_part(3,0,rotation,type);
            }break;
            case Tetrimino_Types::S :
            {
                create_part(0,1,rotation,type);
                create_part(1,1,rotation,type);
                create_part(1,0,rotation,type);
                create_part(2,0,rotation,type);
            }break;
            case Tetrimino_Types::Z :
            {
                create_part(0,0,rotation,type);
                create_part(1,0,rotation,type);
                create_part(1,1,rotation,type);
                create_part(2,1,rotation,type);
            }break;
            case Tetrimino_Types::L :
            {
                create_part(0,1,rotation,type);
                create_part(0,0,rotation,type);
                create_part(1,0,rotation,type);
                create_part(2,0,rotation,type);
            }break;
            case Tetrimino_Types::J :
            {
                create_part(0,0,rotation,type);
                create_part(1,0,rotation,type);
                create_part(2,0,rotation,type);
                create_part(2,1,rotation,type);
            }break;
            case Tetrimino_Types::T :
            {
                create_part(0,0,rotation,type);
                create_part(1,0,rotation,type);
                create_part(1,1,rotation,type);
                create_part(2,0,rotation,type);
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
            sf::RectangleShape* shape = static_cast<sf::RectangleShape*>(fixture->GetUserData());
            fixture->SetUserData(nullptr);
            delete shape;
        }
        _world.DestroyBody(_body);
    }

    b2Fixture* Piece::create_part(int pos_x,int pos_y,float rotation,Tetrimino_Types type)
    {
        b2PolygonShape b2shape;
        b2shape.SetAsBox(converter::pixel_to_meters<double>(BOOK_BOX_SIZE/2),converter::pixel_to_meters<double>(BOOK_BOX_SIZE/2),
                         b2Vec2(converter::pixel_to_meters<double>(BOOK_BOX_SIZE/2*(pos_x+1)),converter::pixel_to_meters<double>(BOOK_BOX_SIZE/2*(pos_y+1))),
                         converter::deg_to_rad(rotation));
        b2Fixture* fixture = _body->CreateFixture(&b2shape,1);

        sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(BOOK_BOX_SIZE,BOOK_BOX_SIZE));
        shape->setOrigin(BOOK_BOX_SIZE*pos_x,BOOK_BOX_SIZE*pos_y);
        shape->setFillColor(Tetrimino_colors[type]);

        fixture->SetUserData(shape);

        return fixture;
    }

    void Piece::update()
    {
        int pos_x = converter::meters_to_pixels(_body->GetPosition().x);
        int pos_y = converter::meters_to_pixels(_body->GetPosition().y);
        float deg = converter::rad_to_deg(_body->GetAngle());

        for(b2Fixture* fixture = _body->GetFixtureList(); fixture != nullptr;fixture=fixture->GetNext())
        {
            sf::RectangleShape* shape = static_cast<sf::RectangleShape*>(fixture->GetUserData());
            shape->setPosition(pos_x,pos_y);
            shape->setRotation(deg);
        } 
    }

    void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(const b2Fixture* fixture=_body->GetFixtureList();fixture!=nullptr;fixture=fixture->GetNext())
        {
            sf::RectangleShape* shape = static_cast<sf::RectangleShape*>(fixture->GetUserData());
            if(shape)
                target.draw(*shape,states);
        }
    }
}
