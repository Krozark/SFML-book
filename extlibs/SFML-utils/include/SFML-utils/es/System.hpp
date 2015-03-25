#ifndef SFUTILS_ES_SYSTEM_HPP
#define SFUTILS_ES_SYSTEM_HPP

#include <SFML-utils/es/defines.hpp>
#include <memory>
#include <unordered_map>

#include <SFML/System.hpp>

namespace sfutils
{
    namespace es
    {
        template<typename ENTITY> class EntityManager;
        template<typename ENTITY> class Entity;

        template<typename ENTITY>
        class VSystem
        {
            public:
                VSystem(const VSystem&) = delete;
                VSystem& operator=(const VSystem&) = delete;

                virtual ~VSystem();

                virtual void update(EntityManager<ENTITY>& entity_manager,const sf::Time& deltaTime) = 0;
            protected:
                VSystem();
                static Family _familyCounter;
        };

        template<typename COMPONENT,typename ENTITY>
        class System : public VSystem<ENTITY>
        {
            public:
                System(const System&) = delete;
                System& operator=(const System&) = delete;

                System();
                virtual ~System();

                static Family family();
        };

        #define __ES_INIT_VSYSTEM__(ENTITY) template<> sfutils::es::Family sfutils::es::VSystem<ENTITY>::_familyCounter = 0;


        template<typename ENTITY>
        class SystemManager
        {
            public:
                SystemManager(const SystemManager&) = delete;
                SystemManager& operator=(const SystemManager&) = delete;

                SystemManager(EntityManager<ENTITY>& manager);
                ~SystemManager();

                template<typename SYSTEM>
                bool add(std::shared_ptr<SYSTEM> ptr);

                template<typename SYSTEM,typename ... Args>
                bool add(Args&& ... args);

                template<typename SYSTEM>
                bool remove();
                
                template<typename SYSTEM>
                std::shared_ptr<SYSTEM> system();

                template<typename SYSTEM>
                void update(const sf::Time& deltaTime);

                void updateAll(const sf::Time& deltaTime);
                
                
            private:
                EntityManager<ENTITY>& _manager;
                std::unordered_map<Family,std::shared_ptr<VSystem<ENTITY>>> _systems;
        };
    }
}
#include <SFML-utils/es/System.tpl>
#endif
