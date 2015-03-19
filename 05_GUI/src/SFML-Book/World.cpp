#include <SFML-Book/World.hpp>
#include <SFML-Book/converter.hpp>
#include <SFML-Book/random.hpp>
#include <SFML-Book/Piece.hpp>

#include <list>

namespace book
{
    World::World(int size_x,int size_y) : _physical_world(b2Vec2(0.f, 1.5f)),_x(size_x), _y(size_y)
    {
        
        createWall(0,0,BOOK_BOX_SIZE,_y*BOOK_BOX_SIZE);
        createWall(BOOK_BOX_SIZE*(_x+1.2),0,BOOK_BOX_SIZE,_y*BOOK_BOX_SIZE);
        createWall(0,BOOK_BOX_SIZE*_y,BOOK_BOX_SIZE*(_x+2.2),BOOK_BOX_SIZE);

#ifdef BOOK_DEBUG
        _physical_world.SetDebugDraw(&_debugDraw);
#endif
    }

    World::~World()
    {
        for (b2Body* body=_physical_world.GetBodyList(); body!=nullptr;)
        {
            b2Body* next = body->GetNext();
            if(body->GetType() == b2_dynamicBody)
                delete static_cast<Piece*>(body->GetUserData());
            else
                delete static_cast<sf::RectangleShape*>(body->GetUserData());
            body = next;
        }
    }

    void World::update(sf::Time deltaTime)
    {
        for (b2Body* body=_physical_world.GetBodyList(); body!=nullptr; body=body->GetNext())
        {
            if(body->GetType() == b2_dynamicBody)
            {
                Piece* piece = static_cast<Piece*>(body->GetUserData());
                piece->update();
            }
        }
        _sounds.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {
                return sound->getStatus() != sf::SoundSource::Status::Playing;
            });

    }

    class __AABB_callback : public b2QueryCallback
    {
        public :
            std::list<b2Fixture*> fixtures;

            virtual bool ReportFixture(b2Fixture* fixture) override
            {
                if(fixture->GetBody()->GetType() == b2_dynamicBody)
                    fixtures.emplace_back(fixture);
                return true;
            }
    };

    int World::clearLines(bool& del,const Piece& current)
    {
        int nb_lines = 0;
        __AABB_callback callback;
        del = false;

        for(int y=0;y<=_y;++y)
        {
            b2AABB aabb;

            aabb.lowerBound = b2Vec2(converter::pixelsToMeters<double>(0),converter::pixelsToMeters<double>((y+0.49)*BOOK_BOX_SIZE));
            aabb.upperBound = b2Vec2(converter::pixelsToMeters<double>(_x*BOOK_BOX_SIZE),converter::pixelsToMeters<double>((y+0.51)*BOOK_BOX_SIZE));

            _physical_world.QueryAABB(&callback,aabb);

            if((int)callback.fixtures.size() >= _x)
            {
                for(b2Fixture* fixture : callback.fixtures)
                {
                    b2Body* body = fixture->GetBody();
                    del |= body == current.getBody();
                    if(body->GetFixtureList()->GetNext() != nullptr)
                    {
                        sf::ConvexShape* shape = static_cast<sf::ConvexShape*>(fixture->GetUserData());
                        body->DestroyFixture(fixture);
                        delete shape;
                    }
                    else
                    {
                        Piece* piece = static_cast<Piece*>(body->GetUserData());
                        delete piece;
                    }

                    fixture = nullptr;
                }
                ++nb_lines;
            }
            callback.fixtures.clear();
        }
        if(nb_lines > 0)
            add(Configuration::Sounds::Explosion);
        return nb_lines;
    }

    void World::updateGravity(int level)
    {
        _physical_world.SetGravity(b2Vec2(0,1.5+(level/2.0)));
    }

    void World::add(Configuration::Sounds sound_id)
    {
        std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds.get(sound_id)));
        sound->setAttenuation(0);
        sound->play();
        _sounds.emplace_back(std::move(sound));
    }

    bool World::isGameOver()const
    {
        for (const b2Body* body=_physical_world.GetBodyList(); body!=nullptr; body=body->GetNext())
        {
            if(body->GetType() == b2_staticBody)
                continue;
            if(body->GetPosition().y < 0)
                return true;
        }
        return false;
    };

    void World::reset()
    {
        for (b2Body* body=_physical_world.GetBodyList(); body!=nullptr;)
        {
            b2Body* next = body->GetNext();
            if(body->GetType() == b2_dynamicBody)
                delete static_cast<Piece*>(body->GetUserData());
            body = next;
        }
    }

    void World::updatePhysics(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();


        _physical_world.Step(seconds,8,3);
    }

    
    Piece* World::newPiece()
    {
        add(Configuration::Sounds::Spawn);
        return new Piece(_physical_world,_x/2*BOOK_BOX_SIZE,BOOK_BOX_SIZE,static_cast<Piece::TetriminoTypes>(random(0,Piece::TetriminoTypes::SIZE-1)),random(0.f,360.f));
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

#ifdef BOOK_DEBUG
    void World::displayDebug()
    {
        _debugDraw.clear();
        _physical_world.DrawDebugData();
        _debugDraw.display();
    }
#endif

    void World::createWall(int pos_x, int pos_y,int size_x,int size_y)
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(converter::pixelsToMeters<double>(pos_x),converter::pixelsToMeters<double>(pos_y));
        bodyDef.type = b2_staticBody;

        b2PolygonShape b2shape;
        double sx = converter::pixelsToMeters<double>(size_x)/2.0;
        double sy = converter::pixelsToMeters<double>(size_y)/2.0;
        b2shape.SetAsBox(sx,sy
                         ,b2Vec2(sx,sy),0);


        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.8;
        fixtureDef.restitution= 0.1;
        fixtureDef.shape = &b2shape;

        b2Body* body = _physical_world.CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);

        sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(size_x,size_y));
        shape->setOrigin(size_x/2.0,size_y/2.0);
        shape->setPosition(sf::Vector2f(pos_x+size_x/2.0,pos_y+size_y/2.0));

        shape->setFillColor(sf::Color(50,50,50));

        body->SetUserData(shape);
    }
    
}
