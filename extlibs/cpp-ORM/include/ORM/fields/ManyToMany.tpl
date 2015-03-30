namespace orm
{
    template<typename T,typename U>
    ManyToMany<T,U>::ManyToMany(T& o) : owner(o), _adds(true)
    {
    }

    template<typename T,typename U>
    M2MQuerySet<T,U> ManyToMany<T,U>::query(DB& db)const
    {
        return M2MQuerySet<T,U>(*this,db);
    }

    template<typename T,typename U>
    typename U::result_type ManyToMany<T,U>::all(DB& db,int max_depth)
    {
#ifdef ORM_USE_CACHE
        if(_adds)
        {
            _cache.clear();
            query(db).get(_cache,max_depth);
            _adds = false;
        }
        return _cache;
#else
        typename U::result_type results;
        query(db).get(results,max_depth);
        return results;
#endif
    };

    template<typename T,typename U>
    void ManyToMany<T,U>::nameAttrs(std::string& q_str,int max_depth,DB& db)
    {
        U::nameAttrs(q_str,ORM_MAKE_NAME(related),max_depth,db);
    }
    
    template<typename T,typename U>
    void ManyToMany<T,U>::nameTables(std::string& q_str,int max_depth,DB& db)
    {
        q_str+= db.escapeColumn(table)+" AS "+db.escapeColumn(table);
        makeJoin(q_str,max_depth,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::makeJoin(std::string& q_str,int max_depth,DB& db)
    {
        const std::string table_alias_T = JOIN_ALIAS(table,ORM_MAKE_NAME(owner));

        q_str+=
            "\nLEFT JOIN "+T::table+" AS "+table_alias_T
            +" ON ("
            +db.escapeColumn(table)+"."+db.escapeColumn(ORM_MAKE_NAME(owner))
            +" = "+db.escapeColumn(table_alias_T)+"."+db.escapeColumn("pk")
            +")\nLEFT JOIN "+U::table+" AS "+ORM_MAKE_NAME(related)
            +" ON ("
            +db.escapeColumn(table)+"."+db.escapeColumn(ORM_MAKE_NAME(linked))
            +" = "+db.escapeColumn(ORM_MAKE_NAME(related))+"."+db.escapeColumn("pk")
            +")";

        U::makeJoin(q_str,ORM_MAKE_NAME(related),max_depth,db);
    }

    template<typename T,typename U>
    bool ManyToMany<T,U>::add(const typename U::type_ptr& obj,DB& db)
    {
        bool res = add(*obj,db);
#ifdef ORM_USE_CACHE
        if(res)
        {
            _adds = true;
            _cache.emplace_back(obj);
        }
#endif
        return res;
    }

    template<typename T,typename U>
    bool ManyToMany<T,U>::add(const U& obj,DB& db)
    {
        if(owner.pk <=0)
        {
            ORM_PRINT_ERROR("The M2M owner as not be saved")
            return false;
        }
        if(obj.pk<=0)
        {
            ORM_PRINT_ERROR("The object must be save to be add in a M2M")
            return false;
        }
        
        std::string q_str = "INSERT INTO "+db.escapeColumn(table)
            +"("+ORM_MAKE_NAME(owner)+","+ORM_MAKE_NAME(linked)+") VALUES ((?),(?));";

        Query& q = *db.prepareQuery(q_str);
        q.set(owner.pk,1);
        q.set(obj.pk,2);

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<BLEU<<"[Sql:insert]"<<q_str<<"\nVALUES = ("<<owner.pk<<", "<<obj.pk<<")"<<BLANC<<std::endl;
        #endif
        
        q.execute();
        q.next();
        delete &q;
        return true;
    };

    template<typename T,typename U>
    void ManyToMany<T,U>::remove(const typename U::type_ptr& obj,DB& db)
    {
        remove(*obj,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::remove(const U& obj,DB& db)
    {
        if(obj.pk<=0 or owner.pk <=0)
            return;

        const std::string table_escaped = db.escapeColumn(table);
        
        std::string q_str = "DELETE FROM "+table_escaped+" WHERE ("
            +table_escaped+"."+db.escapeColumn(ORM_MAKE_NAME(owner))+" = (?)"
            +" AND "
            +table_escaped+"."+db.escapeColumn(ORM_MAKE_NAME(linked))+" = (?))";

        Query& q = *db.prepareQuery(q_str);
        q.set(owner.pk,1);
        q.set(obj.pk,2);

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<COMMENTAIRE<<q_str<<"\nVALUES = ("<<owner.pk<<", "<<obj.pk<<")"<<BLANC<<std::endl;
        #endif
        
        q.execute();
        q.next();
        delete &q;

    };

    template<typename T,typename U>
    bool ManyToMany<T,U>::create(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_CREATE_TABLE
        std::cerr<<MAGENTA<<"[CREATE] create table "<<table<<BLANC<<std::endl;
        #endif
        
        static std::vector<const VAttr*> column_attrs = {
            new FK<T,false>(ORM_MAKE_NAME(owner)),
            new FK<U,false>(ORM_MAKE_NAME(linked))
        }; ///< attr of the class
        bool res = db.create(table,column_attrs);
        delete reinterpret_cast<const FK<T,false>*>(column_attrs[0]);
        delete reinterpret_cast<const FK<U,false>*>(column_attrs[1]);

        return res;
    }

    template<typename T,typename U>
    bool ManyToMany<T,U>::drop(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_DROP_TABLE
        std::cerr<<MAGENTA<<"[DROP] drop table "<<table<<BLANC<<std::endl;
        #endif
        return db.drop(table);
    }

    template<typename T,typename U>
    bool ManyToMany<T,U>::clear(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_TRUNCATE_TABLE
        std::cerr<<MAGENTA<<"[TRUNCATE] truncate table "<<table<<BLANC<<std::endl;
        #endif
        return db.clear(table);
    }

    /*
    template <typename OWNER,typename RELATED,typename T, typename ... Args>
    FilterSet<ManyToMany<OWNER,RELATED>> M2MQ(T&& value,Args&& ... args)
    {
        return FilterSet<ManyToMany<OWNER,RELATED>>(Filter<ManyToMany<OWNER,RELATED>,T>(std::forward<T>(value),std::forward<Args>(args)...));
    }
    */
}
