#ifndef SFUTILS_ES_ENTITYMANAGER_HPP
#define SFUTILS_ES_ENTITYMANAGER_HPP

#include <list>
#include <vector>
#include <bitset>
#include <cstdint>
#include <tuple>
#include <algorithm>
#include <cassert>

#include <utils/memory.hpp>
#include <SFML-utils/es/defines.hpp>

namespace sfutils
{
    namespace es
    {
        template<typename COMPONENT,typename ENTITY> class ComponentHandle;
        template<typename COMPONENT,typename ENTITY> class Component;

        template<class ENTITY>
        class EntityManager
        {
            template<typename ...> class View;
            public:
                using container=std::list<std::uint32_t>;

                EntityManager(const EntityManager&) = delete;
                EntityManager& operator=(const EntityManager&) = delete;

                EntityManager();
                ~EntityManager();

                template<typename ... Args>
                std::uint32_t create(Args&& ... args);

                template<typename ... Args>
                void emplace(std::uint32_t id,Args&& ... args);


                void remove(std::size_t id);

                void update();

                void reset();

                std::size_t size()const;

                bool isValid(std::uint32_t id)const;

                const ENTITY& get(std::size_t id)const;
                ENTITY& get(std::size_t id);

                const ENTITY* getPtr(std::size_t id)const;
                ENTITY* getPtr(std::size_t id);

                container::const_iterator begin()const;
                container::const_iterator end()const;

                template<typename COMPONENT,typename ... Args>
                void addComponent(std::uint32_t id,Args&& ... args);
                
                template<typename COMPONENT>
                void removeComponent(std::uint32_t id);

                template<typename COMPONENT>
                bool hasComponent(std::uint32_t id)const;

                template<typename COMPONENT>
                ComponentHandle<COMPONENT,ENTITY> getComponent(std::uint32_t id)const;

                template<typename ... COMPONENT>
                std::tuple<ComponentHandle<COMPONENT,ENTITY>...> getComponents(std::uint32_t id)const;
                

                template<typename ... COMPONENT>
                View<COMPONENT ...> getByComponents(ComponentHandle<COMPONENT,ENTITY>& ... components);

            private:
                std::vector<ENTITY*> _entitiesAllocated;
                std::vector<std::bitset<MAX_COMPONENTS>> _entitiesComponentsMask;
                std::vector<utils::memory::VPool*> _componentsEntities;

                container _entitiesIndex;
                container _entitiesIndexFree;
                container _entitiesIndexToDestroy;

                inline void reset(std::uint32_t id);

                template<typename COMPONENT>
                void checkComponent();

                template<typename,typename> friend class ComponentHandle;

                template<typename COMPONENT>
                COMPONENT* getComponentPtr(std::uint32_t id)const;

                template<typename ... COMPONENT>
                class View
                {
                    class iterator;
                    public:
                        View(EntityManager<ENTITY>& manager,const std::bitset<MAX_COMPONENTS>& mask,ComponentHandle<COMPONENT,ENTITY>& ... components);

                        iterator begin();
                        iterator end();

                    private:
                        class iterator
                        {
                            public:
                                iterator(View& view,EntityManager<ENTITY>::container::iterator it,EntityManager<ENTITY>::container::iterator it_end);
                                iterator& operator++(); //prefix increment
                                ENTITY* operator*() const;
                                ENTITY* operator->() const;
                                bool operator==(const iterator& other);
                                bool operator!=(const iterator& other);
                            private:
                                View& _view;
                                EntityManager<ENTITY>::container::iterator _it;
                                EntityManager<ENTITY>::container::iterator _itEnd;
                        };

                        template<int N,typename C>
                        void unpackId(std::uint32_t id);

                        template<int N,typename C0,typename C1,typename ... Cx>
                        void unpackId(std::uint32_t id);

                        template<int N,typename C>
                        void unpackManager();

                        template<int N,typename C0,typename C1,typename ... Cx>
                        void unpackManager();

                        EntityManager<ENTITY>& _manager;
                        const std::bitset<MAX_COMPONENTS> _mask;
                        std::tuple<ComponentHandle<COMPONENT,ENTITY>& ...> _handles;
                };
        };
    }
}
#include <SFML-utils/es/EntityManager.tpl>
#endif
