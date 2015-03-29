namespace orm
{
    template<typename T,typename U>
    ManyToMany<T,U>::ManyToMany(T& _owner) : owner(_owner)
    {
    }

    template<typename T,typename U>
    M2MQuerySet<T,U> ManyToMany<T,U>::query(DB& db)const
    {
        return M2MQuerySet<T,U>(*this,db);
    }

    template<typename T,typename U>
    std::list<typename Cache<U>::type_ptr> ManyToMany<T,U>::all(DB& db,int max_depth) const
    {
        std::list<typename Cache<U>::type_ptr> results;
        query(db).get(results,max_depth);
        return results;
    };

    template<typename T,typename U>
    void ManyToMany<T,U>::nameAttrs(std::string& q_str,int max_depth,DB& db)
    {
        U::nameAttrs(q_str,_related,max_depth,db);
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
        const std::string table_alias_T = JOIN_ALIAS(table,_owner);

        q_str+=
            "\nLEFT JOIN "+T::table+" AS "+table_alias_T
            +" ON ("
            +db.escapeColumn(table)+"."+db.escapeColumn(_owner)
            +" = "+db.escapeColumn(table_alias_T)+"."+db.escapeColumn("id")
            +")\nLEFT JOIN "+U::table+" AS "+_related
            +" ON ("
            +db.escapeColumn(table)+"."+db.escapeColumn(_linked)
            +" = "+db.escapeColumn(_related)+"."+db.escapeColumn("id")
            +")";

        U::makeJoin(q_str,_related,max_depth,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::add(const typename Cache<U>::type_ptr& obj,DB& db)
    {
        add(*obj,db);
    }

    template<typename T,typename U>
    void ManyToMany<T,U>::add(const U& obj,DB& db)
    {
        if(owner.pk <=0)
        {
            ORM_PRINT_ERROR("The M2M owner as not be saved")
            return;
        }
        if(obj.pk<=0)
        {
            ORM_PRINT_ERROR("The object must be save to be add in a M2M")
            return;
        }
        
        std::string q_str = "INSERT INTO "+db.escapeColumn(table)
            +"("+_owner+","+_linked+") VALUES ((?),(?));";

        Query& q = *db.prepareQuery(q_str);
        q.set(owner.pk,1);
        q.set(obj.pk,2);

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<BLEU<<"[Sql:insert]"<<q_str<<"\nVALUES = ("<<owner.pk<<", "<<obj.pk<<")"<<BLANC<<std::endl;
        #endif
        
        q.execute();
        q.next();
        delete &q;
    };

    template<typename T,typename U>
    void ManyToMany<T,U>::remove(const typename Cache<U>::type_ptr& obj,DB& db)
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
            +table_escaped+"."+db.escapeColumn(_owner)+" = (?)"
            +" AND "
            +table_escaped+"."+db.escapeColumn(_linked)+" = (?))";

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
            new FK<T,false>(_owner),
            new FK<U,false>(_linked)
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
