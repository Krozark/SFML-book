#include <SFML-utils/es/EntityManager.hpp>
#include <cassert>

namespace sfutils
{
    namespace es
    {
        //////////////// COMPONENT HANDLE ///////////////

        template<typename COMPONENT,typename ENTITY>
        inline bool ComponentHandle<COMPONENT,ENTITY>::isValid()const
        {
            return _manager and _manager->isValid(_entityId) and _manager->template hasComponent<COMPONENT>(_entityId);
        }

        template<typename COMPONENT,typename ENTITY>
        ComponentHandle<COMPONENT,ENTITY>::ComponentHandle() : _manager(nullptr), _entityId(-1)
        {
        }

        template<typename COMPONENT,typename ENTITY>
        ComponentHandle<COMPONENT,ENTITY>::ComponentHandle(const EntityManager<ENTITY>* manager,std::uint32_t entity_id) : _manager(manager), _entityId(entity_id)
        {
        }

        template<typename COMPONENT,typename ENTITY>
        inline COMPONENT* ComponentHandle<COMPONENT,ENTITY>::get()
        {
            assert(isValid());
            return _manager->template getComponentPtr<COMPONENT>(_entityId);
        }

        template<typename COMPONENT,typename ENTITY>
        inline const COMPONENT* ComponentHandle<COMPONENT,ENTITY>::get()const
        {
            assert(isValid());
            return _manager->template getComponentPtr<COMPONENT>(_entityId);
        }

        template<typename COMPONENT,typename ENTITY>
        inline COMPONENT* ComponentHandle<COMPONENT,ENTITY>::operator->()
        {
            assert(isValid());
            return _manager->template getComponentPtr<COMPONENT>(_entityId);
        }

        template<typename COMPONENT,typename ENTITY>
        inline const COMPONENT* ComponentHandle<COMPONENT,ENTITY>::operator->()const
        {
            assert(isValid());
            return _manager->template getComponentPtr<COMPONENT>(_entityId);
        }

        ////////////////// COMPONENT //////////////////
        
        template<typename ENTITY>
        VComponent<ENTITY>::VComponent() : _manager(nullptr), _ownerId(-1)
        {
        }

        template<typename ENTITY>
        VComponent<ENTITY>::~VComponent()
        {
        }

        template<typename ENTITY>
        std::uint32_t VComponent<ENTITY>::ownerId()const
        {
            return _ownerId;
        }


        ////////////////// COMPONENT //////////////////
        template<typename COMPONENT,typename ENTITY>
        Component<COMPONENT,ENTITY>::Component()
        {
        }

        template<typename COMPONENT,typename ENTITY>
        Component<COMPONENT,ENTITY>::~Component()
        {
        }

        template<typename COMPONENT,typename ENTITY>
        inline void Component<COMPONENT,ENTITY>::remove()
        {
            VComponent<ENTITY>::_manager->template removeComponent<COMPONENT>(VComponent<ENTITY>::_ownerId);
        }


        template<typename COMPONENT,typename ENTITY>
        Family Component<COMPONENT,ENTITY>::family()
        {
            static Family family = VComponent<ENTITY>::_familyCounter++;
            assert(family < MAX_COMPONENTS);
            return family;
        }
        
    }
}
