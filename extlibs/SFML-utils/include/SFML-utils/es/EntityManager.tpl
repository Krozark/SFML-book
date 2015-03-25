#include <SFML-utils/es/Component.hpp>

namespace sfutils
{
    namespace es
    {
        template<class ENTITY>
        EntityManager<ENTITY>::EntityManager()
        {
        }

        template<class ENTITY>
        EntityManager<ENTITY>::~EntityManager()
        {
            reset();
        }

        template<class ENTITY>
        template<typename ... Args>
        std::uint32_t EntityManager<ENTITY>::create(Args&& ... args)
        {
            std::uint32_t index = 0;
            if(not _entitiesIndexFree.empty())
            {
                //reuse existing entity
                index = _entitiesIndexFree.front();
                _entitiesIndexFree.pop_front();
                _entitiesAllocated[index] = new ENTITY(this,index,std::forward<Args>(args)...);
            }
            else
            {
                _entitiesComponentsMask.emplace_back();

                index = _entitiesAllocated.size();
                _entitiesAllocated.emplace_back(nullptr);

                //resize components
                auto comp_size = _componentsEntities.size();
                for(std::size_t i=0;i<comp_size;++i)
                {
                    if(_componentsEntities[i] != nullptr)
                        _componentsEntities[i]->resize(index+1);
                }

                //create new entity
                _entitiesAllocated[index] = new ENTITY(this,index,std::forward<Args>(args)...);

            }
            _entitiesIndex.emplace_back(index);

            return index;

        }

        template<class ENTITY>
        template<typename ... Args>
        void EntityManager<ENTITY>::emplace(std::uint32_t id,Args&& ... args)
        {
            //container to small
            std::size_t size = _entitiesAllocated.size();
            if(size <= id) //resize it
            {
                _entitiesAllocated.resize(id+1,nullptr);
                _entitiesComponentsMask.resize(id+1,0);
                _entitiesIndex.emplace_back(id);

                for(size_t i = size;i<id;++i)
                    _entitiesIndexFree.emplace_back(i);

                auto comp_size = _componentsEntities.size();
                for(std::size_t i=0;i<comp_size;++i)
                {
                    if(_componentsEntities[i] != nullptr)
                        _componentsEntities[i]->resize(id+1);
                }
            }
            else if(_entitiesAllocated[id] != nullptr) //already in use
            {
                reset(id);
            }
            else //already free
            {
                _entitiesIndexFree.remove(id);
                _entitiesIndex.emplace_back(id);
            }
            
            _entitiesAllocated[id] = new ENTITY(this,id,std::forward<Args>(args)...);
        }

        template<class ENTITY>
        void EntityManager<ENTITY>::remove(std::size_t id)
        {
            _entitiesIndexToDestroy.emplace_back(id);
        }

        template<class ENTITY>
        void EntityManager<ENTITY>::update()
        {
            if(_entitiesIndexToDestroy.size() > 0)
            {
                auto end = _entitiesIndexToDestroy.end();
                for(auto it = _entitiesIndexToDestroy.begin();it!=end;++it)
                {
                    std::uint32_t id = *it;
                    ENTITY* e = _entitiesAllocated.at(id);
                    if(e != nullptr)
                    {
                        reset(id);

                        _entitiesIndex.erase(std::find(_entitiesIndex.begin(),_entitiesIndex.end(),id));
                        _entitiesIndexFree.emplace_back(id);
                    }
                }
                _entitiesIndexToDestroy.clear();
            }
        }

        template<class ENTITY>
        void EntityManager<ENTITY>::reset()
        {
            _entitiesIndexFree.clear();
            _entitiesIndex.clear();

            auto comp_size = _componentsEntities.size();
            for(std::size_t i=0;i<comp_size;++i)
            {
                if(_componentsEntities[i] != nullptr)
                {
                    for(size_t i = 0;i<_entitiesIndex.size();++i)
                        _componentsEntities[i]->erase<VComponent<ENTITY>>(i);
                    delete _componentsEntities[i];
                }
            }
            _componentsEntities.clear();

            _entitiesComponentsMask.clear();

            size_t size = _entitiesAllocated.size();
            for(size_t i=0;i<size;++i)
                delete _entitiesAllocated[i];

            _entitiesAllocated.clear();
        }

        template<class ENTITY>
        std::size_t EntityManager<ENTITY>::size()const
        {
            return _entitiesAllocated.size() - _entitiesIndexFree.size();
        }

        template<class ENTITY>
        bool EntityManager<ENTITY>::isValid(std::uint32_t id)const
        {
            return id < _entitiesAllocated.size() and _entitiesAllocated[id] != nullptr;
        }


        template<class ENTITY>
        const ENTITY& EntityManager<ENTITY>::get(std::size_t id) const
        {
            return *_entitiesAllocated.at(id);
        }

        template<class ENTITY>
        ENTITY& EntityManager<ENTITY>::get(std::size_t id)
        {
            return *_entitiesAllocated.at(id);
        }

        template<class ENTITY>
        const ENTITY* EntityManager<ENTITY>::getPtr(std::size_t id)const
        {
            return _entitiesAllocated.at(id);
        }

        template<class ENTITY>
        ENTITY* EntityManager<ENTITY>::getPtr(std::size_t id)
        {
            return _entitiesAllocated.at(id);
        }

        template<class ENTITY>
        EntityManager<ENTITY>::container::const_iterator EntityManager<ENTITY>::begin()const
        {
            return _entitiesIndex.cbegin();
        }

        template<class ENTITY>
        EntityManager<ENTITY>::container::const_iterator EntityManager<ENTITY>::end()const
        {
            return _entitiesIndex.cend();
        }


        template<class ENTITY>
        template<typename COMPONENT,typename ... Args>
        void EntityManager<ENTITY>::addComponent(std::uint32_t id,Args&& ... args)
        {
            checkComponent<COMPONENT>();
            Family family = COMPONENT::family();

            assert(not _entitiesComponentsMask.at(id).test(family));

            auto pool = static_cast<utils::memory::Pool<COMPONENT>*>(_componentsEntities[family]);
            pool->emplace(id,std::forward<Args>(args)...);

            pool->at(id)._ownerId = id;
            pool->at(id)._manager = this;

            _entitiesComponentsMask.at(id).set(family);
        }
        
        template<class ENTITY>
        template<typename COMPONENT>
        void EntityManager<ENTITY>::removeComponent(std::uint32_t id)
        {
            checkComponent<COMPONENT>();
            Family family = COMPONENT::family();

            assert(_entitiesComponentsMask.at(id).test(family));

            static_cast<utils::memory::Pool<COMPONENT>*>(_componentsEntities[family])->erase(id);

            _entitiesComponentsMask[id].reset(family);
        }

        template<class ENTITY>
        template<typename COMPONENT>
        inline bool EntityManager<ENTITY>::hasComponent(std::uint32_t id)const
        {
            //checkComponent<COMPONENT>();
            Family family = COMPONENT::family();
            return _entitiesComponentsMask.at(id).test(family);
        }

        template<class ENTITY>
        template<typename COMPONENT>
        inline ComponentHandle<COMPONENT,ENTITY> EntityManager<ENTITY>::getComponent(std::uint32_t id)const
        {
            if(hasComponent<COMPONENT>(id))
                return ComponentHandle<COMPONENT,ENTITY>(this,id);
            return ComponentHandle<COMPONENT,ENTITY>();
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        inline std::tuple<ComponentHandle<COMPONENT,ENTITY>...> EntityManager<ENTITY>::getComponents(std::uint32_t id)const
        {
            return std::make_tuple(getComponent<COMPONENT>(id)...);
        }

        template<class ENTITY>
        template<typename COMPONENT>
        inline COMPONENT* EntityManager<ENTITY>::getComponentPtr(std::uint32_t id)const
        {
            Family family = COMPONENT::family();
            return &static_cast<utils::memory::Pool<COMPONENT>*>(_componentsEntities[family])->at(id);
        }

        template<typename COMPONENT>
        inline void getMask(std::bitset<MAX_COMPONENTS>& mask)
        {
            mask.set(COMPONENT::family());
        }

        template<typename C1, typename C2, typename ... COMPONENT>
        inline void getMask(std::bitset<MAX_COMPONENTS>& mask)
        {
            mask.set(C1::family());
            getMask<C2,COMPONENT...>(mask);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        EntityManager<ENTITY>::View<COMPONENT ...> EntityManager<ENTITY>::getByComponents(ComponentHandle<COMPONENT,ENTITY>& ... components)
        {
            std::bitset<MAX_COMPONENTS> mask;
            getMask<COMPONENT ...>(mask);
            return View<COMPONENT...>(*this,mask,components ...);
        }

        template<class ENTITY>
        void EntityManager<ENTITY>::reset(std::uint32_t id)
        {
            ENTITY* e = _entitiesAllocated.at(id);

            auto comp_size = _componentsEntities.size();
            for(std::size_t i=0;i<comp_size;++i)
            {
                if(_componentsEntities[i] != nullptr)
                    _componentsEntities[i]->erase<VComponent<ENTITY>>(id);
            }
            _entitiesComponentsMask.at(id) = 0;

            delete e;
            _entitiesAllocated[id] = nullptr;
        }


        template<class ENTITY>
        template<typename COMPONENT>
        inline void EntityManager<ENTITY>::checkComponent()
        {
            Family family = COMPONENT::family();
            //resize
            if( _componentsEntities.size() <= family)
                _componentsEntities.resize(family+1,nullptr);
            //check Pool validity
            if(_componentsEntities[family] == nullptr)
            {
                auto pool = new utils::memory::Pool<COMPONENT>;
                pool->resize(_entitiesAllocated.size());
                _componentsEntities[family] = pool;
            }
        }

        /////////////////////// VIEW ///////////////////

        template<class ENTITY>
        template<typename ... COMPONENT>
        EntityManager<ENTITY>::View<COMPONENT...>::View(EntityManager<ENTITY>& manager,const std::bitset<MAX_COMPONENTS>& mask,ComponentHandle<COMPONENT,ENTITY>& ... components) : _manager(manager), _mask(mask), _handles(std::tuple<ComponentHandle<COMPONENT,ENTITY>&...>(components ...))
        {
            unpackManager<0,COMPONENT ...>();
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        inline typename EntityManager<ENTITY>::template View<COMPONENT ...>::iterator EntityManager<ENTITY>::View<COMPONENT ...>::begin()
        {
            auto begin = _manager._entitiesIndex.begin();
            auto end = _manager._entitiesIndex.end();

            while(begin != end)
            {
                std::uint32_t index = *begin;    
                if((_manager._entitiesComponentsMask[index] & _mask) == _mask)
                {
                    unpackId<0,COMPONENT...>(index);
                    break;
                }
                ++begin;
            }

            return iterator(*this,begin,end);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        inline typename EntityManager<ENTITY>::template View<COMPONENT ...>::iterator EntityManager<ENTITY>::View<COMPONENT ...>::end()
        {
            return iterator(*this,_manager._entitiesIndex.end(),_manager._entitiesIndex.end());
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        template<int N,typename C>
        inline void EntityManager<ENTITY>::View<COMPONENT...>::unpackId(std::uint32_t id)
        {
            std::get<N>(_handles)._entityId = id;
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        template<int N,typename C0,typename C1,typename ... Cx>
        inline void EntityManager<ENTITY>::View<COMPONENT...>::unpackId(std::uint32_t id)
        {
            unpackId<N,C0>(id);
            unpackId<N+1,C1,Cx ...>(id);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        template<int N,typename C>
        inline void EntityManager<ENTITY>::View<COMPONENT...>::unpackManager()
        {
            std::get<N>(_handles)._manager = &_manager;
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        template<int N,typename C0,typename C1,typename ... Cx>
        inline void EntityManager<ENTITY>::View<COMPONENT...>::unpackManager()
        {
            unpackManager<N,C0>();
            unpackManager<N+1,C1,Cx ...>();
        }

        ////////////////// VIEW ITERATOR /////////////////////////

        template<class ENTITY>
        template<typename ... COMPONENT>
        EntityManager<ENTITY>::View<COMPONENT ...>::iterator::iterator(View& view,EntityManager<ENTITY>::container::iterator it,EntityManager<ENTITY>::container::iterator it_end) : _view(view), _it(it), _itEnd(it_end)
        {
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        typename EntityManager<ENTITY>::template View<COMPONENT...>::iterator& EntityManager<ENTITY>::View<COMPONENT ...>::iterator::operator++()
        {
            ++_it;
            while(_it != _itEnd)
            {
                std::uint32_t index = *_it;    
                if(_view._manager._entitiesAllocated.at(index) != nullptr and (_view._manager._entitiesComponentsMask.at(index) & _view._mask) == _view._mask)
                {
                    _view.unpackId<0,COMPONENT...>(index);
                    break;
                }
                ++_it;
            }
            return *this;
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        inline ENTITY* EntityManager<ENTITY>::View<COMPONENT ...>::iterator::operator*()const
        {
            if(_it == _itEnd)
                return nullptr;
            return _view._manager._entitiesAllocated.at(*_it);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        inline ENTITY* EntityManager<ENTITY>::View<COMPONENT ...>::iterator::operator->()const
        {
            if(_it == _itEnd)
                return nullptr;
            return _view._manager._entitiesAllocated.at(*_it);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        bool EntityManager<ENTITY>::View<COMPONENT ...>::iterator::operator==(const EntityManager<ENTITY>::View<COMPONENT...>::iterator& other)
        {
            return _it == other._it and _view._mask == other._view._mask and &(_view._manager) == &(other._view._manager);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        bool EntityManager<ENTITY>::View<COMPONENT...>::iterator::operator!=(const EntityManager<ENTITY>::View<COMPONENT...>::iterator& other)
        {
            return _it != other._it or _view._mask != other._view._mask or &(_view._manager) != &(other._view._manager);
        }

    }
}
