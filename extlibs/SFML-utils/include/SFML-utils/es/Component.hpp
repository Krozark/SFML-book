#ifndef SFUTILS_ES_COMPONENT_HPP
#define SFUTILS_ES_COMPONENT_HPP

#include <SFML-utils/es/defines.hpp>
#include <cstdint>

namespace sfutils
{
    namespace es
    {
        template<typename ENTITY> class EntityManager;
        template<typename COMPONENT,typename ENTITY> class Component;
        
        template<typename COMPONENT,typename ENTITY>
        class ComponentHandle
        {
            public:
                ComponentHandle(const ComponentHandle&) = default;
                ComponentHandle& operator=(const ComponentHandle&) = default;

                ComponentHandle();

                bool isValid()const;

                COMPONENT* get();
                const COMPONENT* get()const;

                COMPONENT* operator->();
                const COMPONENT* operator->()const;

            private:
                friend class EntityManager<ENTITY>;

                ComponentHandle(const EntityManager<ENTITY>* manager,std::uint32_t entity_id);

                const EntityManager<ENTITY>* _manager;
                std::uint32_t _entityId;    
        };


        template<typename ENTITY>
        class VComponent
        {
            public:
                virtual ~VComponent();

                std::uint32_t ownerId()const;

            protected:
                friend class EntityManager<ENTITY>;

                VComponent();

                EntityManager<ENTITY>* _manager;
                std::uint32_t _ownerId;    

                static Family _familyCounter;
        };

        #define __ES_INIT_VCOMPONENT__(ENTITY) template<> sfutils::es::Family sfutils::es::VComponent<ENTITY>::_familyCounter = 0;

        template<typename COMPONENT,typename ENTITY>
        class Component : public VComponent<ENTITY>
        {
            public:
                Component(const Component&) = delete;
                Component& operator=(const Component&) = delete;

                Component();
                virtual ~Component();
                
                void remove();
                static Family family();

                typedef ComponentHandle<COMPONENT,ENTITY> Handle;
        };

    }
}
#include <SFML-utils/es/Component.tpl>
#endif
