namespace orm
{
    template<typename T>
    Cache<T>::Cache()
    {
        #ifdef ORM_USE_CACHE
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<MAGENTA<<"[Register] Cache of "<<T::table<<BLANC<<std::endl;
        #endif
        #endif
    };

    template<typename T>
    Cache<T>::~Cache()
    {
        #ifdef ORM_USE_CACHE
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<MAGENTA<<"[Delete] Cache of "<<T::table<<BLANC<<std::endl;
        #endif
        #endif
    }

    template<typename T>
    typename Cache<T>::type_ptr Cache<T>::getOrCreate(const unsigned int& pk,DB& db,int max_depth)
    {
        //std::lock_guard<std::mutex> lock(_mutex);//lock
        //already existe
        #ifdef ORM_USE_CACHE
        const auto& res= map.find(pk);
        if(res != map.end())
            return res->second;
        #endif

        type_ptr ptr = T::_get_ptr(pk,db,max_depth);
        if(ptr.get() == nullptr)
            ptr = T::create();

        #ifdef ORM_USE_CACHE
        map[pk] = ptr;
        return map[pk];
        #else
        return type_ptr(ptr);
        #endif
    }

    template<typename T>
    typename Cache<T>::type_ptr Cache<T>::getOrCreate(const unsigned int& pk,const Query& query,int& prefix,int max_depth)
    {
        #ifdef ORM_USE_CACHE
        const auto& res= map.find(pk);
        if(res != map.end())
        {
            T::incDepth(prefix,max_depth);
            return res->second;
        }
        type_ptr& r= map[pk];
        r = T::createFromDB(query,prefix,max_depth);
        #else
        type_ptr r = T::createFromDB(query,prefix,max_depth);
        #endif
        return r;
    }

    template<typename T>
    typename Cache<T>::type_ptr Cache<T>::getOrCreate(const Query& query,int max_depth)
    {
        int pk = -1;
        int index = query.db.getInitialGetcolumnNumber();
        query.get(pk,index);

        #ifdef ORM_USE_CACHE
        const auto& res= map.find(pk);

        if(res != map.end())
            return res->second;

        type_ptr& r= map[pk];
        r = T::createFromDB(query,--index,max_depth);

        #else
        type_ptr r = T::createFromDB(query,--index,max_depth);
        #endif
        return r;
    }



    template<typename T>
    void Cache<T>::__print__()
    {
        #ifdef ORM_USE_CACHE
        for(auto& i : map)
            std::cerr<<*i.second<<std::endl;
        #endif
    }

    template<typename T>
    void Cache<T>::clear(bool reset_pk)
    {
        #ifdef ORM_USE_CACHE
        if(reset_pk)
        {
            for(auto& i : map)
                i.second->pk = -1;

        }
        map.clear();
        #endif
    }

/////////////////// PRIVATE ////////////////////

    template<typename T>
    typename Cache<T>::type_ptr& Cache<T>::add(typename Cache<T>::type_ptr& obj)
    {
        #ifdef ORM_USE_CACHE
        const auto& res=map.find(obj->pk);
        if(res != map.end())
        {
            return res->second;
        }
        map[obj->pk] = obj;
        #endif
        return obj;
    }

    template<typename T>
    void Cache<T>::del(const unsigned int& pk)
    {
        #ifdef ORM_USE_CACHE
        map.erase(pk);
        #endif
    }


}
