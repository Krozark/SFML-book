#include <SFML-utils/ES.hpp>

#include <iostream>

#include <SFML/System.hpp>

using namespace sfutils;

struct Component1 : Component<Component1,DefaultEntity>
{
    explicit Component1(float f) : _f(f){};

    float _f;
};

struct Component2 : Component<Component2,DefaultEntity>
{
    explicit Component2(int i,const std::string& str) : _i(i), _str(str){};

    int _i;
    std::string _str;
};


struct System1 : System<System1,DefaultEntity>
{
    virtual void update(EntityManager<DefaultEntity>& manager,const sf::Time& dt) override
    {
        std::cout<<"System1::update("<<dt.asSeconds()<<") manage entities with Component1 only"<<std::endl;

        Component1::Handle component;
        auto view = manager.getByComponents(component);

        auto begin = view.begin();
        auto end = view.end();

        while(begin != end)
        {
            std::cout<<"Entity id: "<<begin->id()<<"\n"
            <<"\t Component1(_f="<<component->_f<<")"<<std::endl;
            ++begin;
        }
    }
};

struct System2 : System<System2,DefaultEntity>
{
    virtual void update(EntityManager<DefaultEntity>& manager,const sf::Time& dt) override
    {
        std::cout<<"System2::update("<<dt.asSeconds()<<") manager entities with Component2 only"<<std::endl;
        Component2::Handle component;
        auto view = manager.getByComponents(component);

        auto begin = view.begin();
        auto end = view.end();

        while(begin != end)
        {
            std::cout<<"Entity id: "<<begin->id()<<"\n"
            <<"\t Component2(_i="<<component->_i<<",_str="<<component->_str<<")"<<std::endl;
            ++begin;
        }
    }
};

struct System3 : System<System3,DefaultEntity>
{
    virtual void update(EntityManager<DefaultEntity>& manager,const sf::Time& dt) override
    {
        std::cout<<"System3::update("<<dt.asSeconds()<<") manager entities with Component1 and Component2"<<std::endl;
        Component1::Handle component1;
        Component2::Handle component2;
        auto view = manager.getByComponents(component1,component2);

        for(auto entity : view)
        {
            std::cout<<"Entity id: "<<entity->id()<<"\n"
            <<"\t Component1(_f="<<component1->_f<<")"
            <<"\t Component2(_i="<<component2->_i<<",_str="<<component2->_str<<")"<<std::endl;
        }
    }
};

struct System4 : System<System4,DefaultEntity>
{
    virtual void update(EntityManager<DefaultEntity>& manager,const sf::Time& dt) override
    {
        int i =0;
        for(auto id : manager)
        {
            DefaultEntity& e = manager.get(id);
            ++i;
        }
        std::cout<<"Process to "<<i<<" entities in "<<dt.asSeconds()<<" seconds. FPS: "<<(1/dt.asSeconds())<<std::endl;
    }

};

struct System5 : System<System5,DefaultEntity>
{
    virtual void update(EntityManager<DefaultEntity>& manager,const sf::Time& dt) override
    {
        int i =0;
        std::uint32_t last_id=0;
        for(auto id : manager)
        {
            DefaultEntity& e = manager.get(id);
            if(i & 1)
                manager.remove(last_id);
            last_id = id;
            ++i;
        }
        for(int j=i/2;j<i;++j)
            manager.create();

        std::cout<<"Process to "<<i<<" entities in "<<dt.asSeconds()<<" seconds. FPS: "<<(1/dt.asSeconds())<<std::endl;
    }

};

int main(int argc,char* argv[])
{

    EntityManager<DefaultEntity> entities;

    {
        std::uint32_t id = entities.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 
    }

    std::cout<<std::endl;

    {
        std::uint32_t id = entities.create();
       std::cout<<"Create entity of id: "<<id<<std::endl; 

        DefaultEntity& e = entities.get(id);
        e.add<Component1>(42);
        /*auto comp =*/ e.component<Component1>();
        std::cout<<"Add Component1(_f=42)"<<std::endl;
    }

    std::cout<<std::endl;

    {
        std::uint32_t id = entities.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 

        DefaultEntity& e = entities.get(id);
        e.add<Component2>(72,"plop");
        /*auto comp =*/ e.component<Component2>();
        std::cout<<"Add Component2(_i=72,_str=\"plop\")"<<std::endl;
    }

    std::cout<<std::endl;

    {
        std::uint32_t id = entities.create();
        std::cout<<"Create entity of id: "<<id<<std::endl; 

        DefaultEntity& e = entities.get(id);
        e.add<Component1>(45.89);
        /*auto comp1 =*/ e.component<Component1>();
        std::cout<<"Add Component1(_f=45.89)"<<std::endl;
        e.add<Component2>(48.9,"test");
        /*auto comp2 =*/ e.component<Component2>();
        std::cout<<"Add Component2(_i=48.9,_str=\"test\")"<<std::endl;
        /*auto comp_all =*/ e.components<Component1,Component2>();
    }

    std::cout<<std::endl;


    SystemManager<DefaultEntity> systems(entities);
    systems.add<System1>();
    systems.add<System2>();
    systems.add(std::shared_ptr<System3>(new System3));
    systems.add<System4>();
    systems.add<System5>();

    std::cout<<"=== update All systems ==="<<std::endl;
    //systems.updateAll(0);

    std::cout<<"=== System1 ==="<<std::endl;
    systems.update<System1>(sf::seconds(1));

    std::cout<<"=== System2 ==="<<std::endl;
    systems.update<System2>(sf::seconds(2));

    std::cout<<"=== System3 ==="<<std::endl;
    systems.update<System3>(sf::seconds(3));

    for(int i = 0; i<1000000;++i)
        /*std::uint32_t id = */entities.create();

    sf::Clock clock;
    while(true)
    {
        systems.update<System4>(clock.restart());
        entities.update();
    }

    return 0;
};
