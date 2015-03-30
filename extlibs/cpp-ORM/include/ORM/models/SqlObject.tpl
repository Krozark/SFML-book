#include <ORM/backends/DB.hpp>
#include <ORM/backends/private/QuerySet.hpp>


namespace orm
{
    template<typename T>
    SqlObject<T>::SqlObject()
    {
    };

    template<typename T>
    T* SqlObject<T>::createFromDB(const Query& query,int& prefix, int max_depth)
    {
        T* res = new T();
        if(not res->loadFromDB(query,prefix,max_depth))
        {
            delete res;
            res = nullptr;
        }
        return res;
    };

    template<typename T>
    typename SqlObject<T>::type_ptr SqlObject<T>::get(const unsigned int& id,DB& db,int max_depth)
    {
        return cache.getOrCreate(id,db,max_depth);
    }
    
    template<typename T>
    T* SqlObject<T>::_get_ptr(const unsigned int id,DB& db,int max_depth)
    {
        if(max_depth <0)
            return 0;

        std::string q_str ="SELECT ";
        nameAttrs(q_str,table,max_depth,db);
                                    
        q_str+="\nFROM ";
        nameTables(q_str,"",max_depth,db);

        q_str+=" \nWHERE ("
        +db.escapeColumn(table)+"."
        +db.escapeColumn("pk")
        +" = "+std::to_string(id)
        +") ";

        Query* q = db.query(q_str);

        T* res = new T();
        if(not q->getObj(*res,max_depth))
        {
            #if ORM_DEBUG & ORM_DEBUG_GET_OBJ
            std::cerr<<ROUGE<<"[GET OBJ] SqlObject<T>::_get_ptr(const unsigned int id,int max_depth) failed"<<BLANC<<std::endl;
            #endif
            delete res;
            res = nullptr;
        }
        delete q;
        return res;
    };

    template<typename T>
    typename SqlObject<T>::result_type SqlObject<T>::all(DB& db,int max_depth)
    {
        result_type results;
        query(db).get(results,max_depth);
        return results;
    };

    template<typename T>
    QuerySet<T> SqlObject<T>::query(DB& db)
    {
        return QuerySet<T>(db);
    }


    template<typename T>
    bool SqlObject<T>::save(bool recursive,DB& db)
    {
        bool res;
        if(recursive)//save all FK
        {
            for(VFK* fk : fks)
                fk->save(recursive,db);
        }
        else//save or create all FK needed (not null)
        {
            for(VFK* fk : fks)
            {
                VFK& fk_tmp = *fk;
                if(fk_tmp.nullable == false and (fk_tmp.fk <=0 or fk_tmp.modify == true))
                    fk_tmp.save(recursive,db);
            }
        }

        if(pk <= 0)
        {

            before_save();
            res = db.save(table,pk,attrs);
            type_ptr ptr = this->as_type_ptr();
            cache.add(ptr);
            after_save();
        }
        else
        {
            before_update();
            res= db.update(table,pk,attrs);
            after_update();
        }
        return res;
    }

    template<typename T>
    bool SqlObject<T>::del(bool recursive,DB& db)
    {
        bool res =true;
        if(db.del(table,pk))
        {
            cache.del(pk);
            pk = -1;
            if(recursive)
            {
                for(VFK* fk : fks)
                {
                    bool tmp = fk->del(recursive,db);
                    res = res && tmp;
                }
            }
            return res;
        }
        return false;
    };

    template<typename T>
    typename SqlObject<T>::type_ptr SqlObject<T>::as_type_ptr()
    {
        return this->shared_from_this();
    }

    template<typename T>
    bool SqlObject<T>::create(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_CREATE_TABLE
        std::cerr<<MAGENTA<<"[CREATE] create table "<<table<<BLANC<<std::endl;
        #endif
        return db.create(table,column_attrs);
    }

    template<typename T>
    bool SqlObject<T>::drop(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_DROP_TABLE
        std::cerr<<MAGENTA<<"[DROP] drop table "<<table<<BLANC<<std::endl;
        #endif
        cache.clear(true);
        return db.drop(table);
    }

    template<typename T>
    bool SqlObject<T>::clear(DB& db)
    {
        #if ORM_DEBUG & ORM_DEBUG_TRUNCATE_TABLE
        std::cerr<<MAGENTA<<"[TRUNCATE] truncate table "<<table<<BLANC<<std::endl;
        #endif
        cache.clear(true);
        return db.clear(table);
    }

    template<typename T>
    void SqlObject<T>::nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db)
    {
        q_str+= db.escapeColumn(prefix)+"."+db.escapeColumn("pk")+" AS "+JOIN_ALIAS(prefix,"pk");
        
        const int size = column_attrs.size();

        for(int i=0;i<size;++i)
        {
            q_str+= column_attrs[i]->makeName(db,prefix,max_depth);
        }
    }

    template<typename T>
    void SqlObject<T>::nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db)
    {
        const std::string table_alias = MAKE_PREFIX(prefix,table);
        const std::string escaped_table_alias = db.escapeColumn(table_alias);

        q_str+=escaped_table_alias+" AS "+escaped_table_alias;

        if(--max_depth>=0)
            makeJoin(q_str,table_alias,max_depth,db);
    }

    template<typename T>
    void SqlObject<T>::makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db)
    {
        const int size = column_fks.size();
        --max_depth;
        for(int i=0;i<size;++i)
        {

            const SqlObjectBase& object = column_fks[i]->getObject(db);
            /*if (&object == NULL)
                continue;*/
            const std::string& col = column_fks[i]->getcolumn();
            const std::string table_alias = MAKE_PREFIX(prefix,col);

            q_str+= "\nLEFT JOIN "+object.getTable()+" AS "+table_alias
                +" ON ("
                +db.escapeColumn(prefix)+"."+db.escapeColumn(col)
                +" = "+db.escapeColumn(table_alias)+"."+db.escapeColumn("pk")
                +")";

            if(max_depth>=0)
                object._makeJoin(q_str,table_alias,max_depth,db);
        }
    }

    template<typename T>
    void SqlObject<T>::_nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const
    {
        SqlObject<T>::nameAttrs(q_str,prefix,max_depth,db);
    }

    template<typename T>
    void SqlObject<T>::_nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const
    {
        SqlObject<T>::nameTables(q_str,prefix,max_depth,db);
    }

    template<typename T>
    void SqlObject<T>::_makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const
    {
        SqlObject<T>::makeJoin(q_str,prefix,max_depth,db);
    }

    template<typename T>
    void SqlObject<T>::incDepth(int& depth,int max_depth)
    {
        depth+= (1 + column_attrs.size()); //id + attrs

        const int _size = column_fks.size();
        for(int i=0;i<_size;++i)
            column_fks[i]->incDepth(depth,max_depth);
    }
};
