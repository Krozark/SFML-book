#include <SFML-Book/World.hpp>
#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/converter.hpp>
#include <SFML-Book/random.hpp>
#include <SFML-Book/Piece.hpp>

namespace book
{
    World::World(int size_x,int size_y) : ActionTarget(Configuration::player_inputs),_physical_world(b2Vec2(0.f, 9.8f)), _current_piece(nullptr), _x(size_x), _y(size_y)
    {
        bind(Configuration::PlayerInputs::HardDrop,[this](const sf::Event&){        
             new Piece(_physical_world,_x/2*BOOK_BOX_SIZE,0,static_cast<Piece::Tetrimino_Types>(random(0,Piece::Tetrimino_Types::SIZE)),random(0.f,360.f));
        });
        
        create_wall(0,0,BOOK_BOX_SIZE,_y*BOOK_BOX_SIZE);
        create_wall(BOOK_BOX_SIZE*_x,0,BOOK_BOX_SIZE,_y*BOOK_BOX_SIZE);
        create_wall(0,BOOK_BOX_SIZE*_y,BOOK_BOX_SIZE*(_x+1),BOOK_BOX_SIZE);

        
    }

    World::~World()
    {
        for (b2Body* body=_physical_world.GetBodyList(); body!=nullptr; body=body->GetNext())
        {
            b2Body* next = body->GetNext();
            delete static_cast<Piece*>(body->GetUserData());
            body = next;
        }
    }

    void World::update(sf::Time deltaTime)
    {
        for (b2Body* body=_physical_world.GetBodyList(); body!=nullptr; body=body->GetNext())
        {
            Piece* piece = static_cast<Piece*>(body->GetUserData());
            piece->update();
        }

    }

    void World::update_physics(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();

        _physical_world.Step(seconds,8,3);
    }

    void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (const b2Body* body=_physical_world.GetBodyList(); body!=nullptr; body=body->GetNext())
        {
            if(body->GetType() == b2_dynamicBody)
            {
                Piece* piece = static_cast<Piece*>(body->GetUserData());
                target.draw(*piece,states);
            }
            else//static
            {
                sf::RectangleShape* shape = static_cast<sf::RectangleShape*>(body->GetUserData());
                target.draw(*shape,states);
            }
        }
    }

    void World::create_wall(int pos_x, int pos_y,int size_x,int size_y)
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(converter::pixel_to_meters<double>(pos_x),converter::pixel_to_meters<double>(pos_y));
        bodyDef.type = b2_staticBody;

        b2PolygonShape b2shape;
        b2shape.SetAsBox(converter::pixel_to_meters<double>(size_x/2.0),converter::pixel_to_meters<double>(size_y/2.0),
                         b2Vec2(0,0),0);

        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.9;
        fixtureDef.restitution= 0.2;
        fixtureDef.shape = &b2shape;

        b2Body* body = _physical_world.CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);

        sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(size_x,size_y));
        shape->setPosition(sf::Vector2f(pos_x,pos_y));

        shape->setFillColor(sf::Color::White);

        body->SetUserData(shape);
    }
    
}
