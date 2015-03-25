#ifndef SFUTILS_ES_ENTITY_HPP
#define SFUTILS_ES_ENTITY_HPP

#include <cstdint>
#include <tuple>
#include <SFML-utils/es/defines.hpp>

#include <SFML-utils/es/System.hpp>
#include <SFML-utils/es/Component.hpp>

namespace sfutils
{
    namespace es
    {

        template<typename ENTITY> class EntityManager;
        template<typename COMPONENT,typename ENTITY> class Component;
        template<typename COMPONENT,typename ENTITY> class ComponentHandle;
        
        template<typename ENTITY>
        class Entity
        {
            public:
                Entity(Entity&&) = default;
                Entity& operator=(Entity&&) = default;

                Entity(EntityManager<ENTITY>* manager,std::uint32_t id);
                ~Entity();

                std::uint32_t id()const;
                EntityManager<ENTITY>& getManager();

                bool operator==(const Entity& other)const;
                bool operator!=(const Entity& other)const;

                void remove();

                template<typename COMPONENT,typename ... Args>
                void add(Args&& ... args);

                template<typename COMPONENT>
                void remove();

                template<typename COMPONENT>
                bool has()const;

                template<typename COMPONENT>
                ComponentHandle<COMPONENT,ENTITY> component()const;

                template<typename ... COMPONENT>
                std::tuple<ComponentHandle<COMPONENT,ENTITY>...> components()const;


            private:
                std::uint32_t _id;    
                EntityManager<ENTITY>* _manager;
        };

        #define ES_INIT_ENTITY(ENTITY) __ES_INIT_VCOMPONENT__(ENTITY);__ES_INIT_VSYSTEM__(ENTITY);

        class DefaultEntity : public Entity<DefaultEntity>
        {
            public:
                using Entity<DefaultEntity>::Entity;

        };

    }
}
#include <SFML-utils/es/Entity.tpl>
#endif
