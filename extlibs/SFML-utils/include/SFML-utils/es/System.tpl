#include <cassert>

namespace sfutils
{
    namespace es
    {
        
        ///////////////// Virtual SYSTEM ///////////////
        //
        template<typename ENTITY>
        VSystem<ENTITY>::VSystem()
        {
        }

        template<typename ENTITY>
        VSystem<ENTITY>::~VSystem()
        {
        }
        ///////////////// SYSTEM ///////////////
        template<typename COMPONENT,typename ENTITY>
        System<COMPONENT,ENTITY>::System()
        {
        }

        template<typename COMPONENT,typename ENTITY>
        System<COMPONENT,ENTITY>::~System()
        {
        }

        template<typename COMPONENT,typename ENTITY>
        Family System<COMPONENT,ENTITY>::family()
        {
            static Family family = VSystem<ENTITY>::_familyCounter++;
            assert(family < MAX_COMPONENTS);
            return family;
        }

        ///////////////// SYSTEM MANAGER ///////////////
        template<typename ENTITY>
        SystemManager<ENTITY>::SystemManager(EntityManager<ENTITY>& manager) : _manager(manager)
        {
        }

        template<typename ENTITY>
        SystemManager<ENTITY>::~SystemManager()
        {
        }

        template<typename ENTITY>
        void SystemManager<ENTITY>::updateAll(const sf::Time& deltaTime)
        {
            for(auto& pair : _systems)
                pair.second->update(_manager,deltaTime);
        }
        
        template<typename ENTITY>
        template<typename SYSTEM>
        bool SystemManager<ENTITY>::add(std::shared_ptr<SYSTEM> ptr)
        {
            if(_systems.count(SYSTEM::family()) == 0)
            {
                _systems.insert(std::make_pair(SYSTEM::family(),ptr));
                return true;
            }
            return false;
        }

        template<typename ENTITY>
        template<typename SYSTEM,typename ... Args>
        bool SystemManager<ENTITY>::add(Args&& ... args)
        {
            if(_systems.count(SYSTEM::family()) == 0)
            {
                _systems.emplace(SYSTEM::family(),std::shared_ptr<SYSTEM>(new SYSTEM(std::forward<Args>(args)...)));
                return true;
            }
            return false;
        }
        
        template<typename ENTITY>
        template<typename SYSTEM>
        bool SystemManager<ENTITY>::remove()
        {
            if(_systems.count(SYSTEM::family()) == 0)
                return false;
            _systems.erase(SYSTEM::family());
            return true;
        }

        template<typename ENTITY>
        template<typename SYSTEM>
        inline std::shared_ptr<SYSTEM> SystemManager<ENTITY>::system()
        {
            return std::static_pointer_cast<SYSTEM>(_systems.at(SYSTEM::family()));
        }

        template<typename ENTITY>
        template<typename SYSTEM>
        inline void SystemManager<ENTITY>::update(const sf::Time& deltaTime)
        {
            system<SYSTEM>()->update(_manager,deltaTime);
        }
    }
}
