#include <SFML-Book/World.hpp>
#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/converter.hpp>

namespace book
{
    World::World(int size_x,int size_y) : ActionTarget(Configuration::player_inputs),_physical_world(b2Vec2(0.f, 9.8f))
    {
    }

    World::~World()
    {
        for (b2Body* body=_physical_world.GetBodyList(); body!=nullptr; body=body->GetNext())
        {
            //delete static_cast<sf::RectangleShape*>(body->GetUserData());
            _physical_world.DestroyBody(body);
        }
    }

    void World::update(sf::Time deltaTime)
    {
        for (b2Body* body=_physical_world.GetBodyList(); body!=nullptr; body=body->GetNext())
        {
            int pos_x = converter::meters_to_pixels(body->GetPosition().x);
            int pos_y = converter::meters_to_pixels(body->GetPosition().y);
            float deg = converter::rad_to_deg(body->GetAngle());

            for(b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr;fixture=fixture->GetNext())
            {
                sf::Shape* shape = static_cast<sf::Shape*>(fixture->GetUserData());
                shape->setPosition(pos_x,pos_y);
                shape->setRotation(deg);
            } 
        }
    }

    void World::update_physics(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();

        _physical_world.Step(seconds,8,3);
    }

    void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        /*for (b2Body* body=_physical_world.GetBodyList(); body!=nullptr; body=body->GetNext())
        {   
            for(b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr;fixture=fixture->GetNext())
            {
                sf::Shape* shape = static_cast<sf::Shape*>(fixture->GetUserData());
                render.draw(*shape);
            }
        }*/
    }
}
