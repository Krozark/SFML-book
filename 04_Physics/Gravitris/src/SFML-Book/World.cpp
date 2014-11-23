#include <SFML-Book/World.hpp>
#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/converter.hpp>
#include <SFML-Book/Piece.hpp>

namespace book
{
    World::World(int size_x,int size_y) : ActionTarget(Configuration::player_inputs),_physical_world(b2Vec2(0.f, 9.8f))
    {
        bind(Configuration::PlayerInputs::HardDrop,[this](const sf::Event&){
             new Piece(_physical_world,100,100,Piece::Tetrimino_Types::J,0);
        });        
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
            Piece* piece = static_cast<Piece*>(body->GetUserData());
            target.draw(*piece,states);
        }
    }
}
