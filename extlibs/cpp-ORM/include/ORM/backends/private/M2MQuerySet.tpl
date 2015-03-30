#include <algorithm>    // std::swap
#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>::M2MQuerySet(const ManyToMany<OWNER,RELATED>& m2m,DB& db): limit_skip(0), limit_count(-1), db(db), m2m(m2m)
    {
        filters.emplace_back(Q<ManyToMany<OWNER,RELATED>>(m2m.owner.pk,op::exact,m2m.ORM_MAKE_NAME(owner)));
    }

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>::~M2MQuerySet()
    {
    }


    template <typename OWNER, typename RELATED>
    template <typename T,typename ... Args>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::filter(T&& v,const std::string& op,Args&& ... args)
    {
        filters.emplace_back(Q<ManyToMany<OWNER,RELATED>>(std::forward<T>(v),op,m2m.ORM_MAKE_NAME(linked),std::forward<Args>(args)...));
        return *this;
    };

    template<typename OWNER,typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::filter(const FilterSet<ManyToMany<OWNER,RELATED>>& f)
    {
        filters.emplace_back(f);
        return *this;
    }

    template<typename OWNER,typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::filter(FilterSet<ManyToMany<OWNER,RELATED>>&& f)
    {
        filters.push_back(std::move(f));
        return *this;
    }

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::orderBy(const std::string& column,const char order)
    {
        if( order == op::desc)
            order_by.push_back(DB::makecolumname(*ManyToMany<OWNER,RELATED>::default_connection,ManyToMany<OWNER,RELATED>::_related,column)+" DESC");
        else
            order_by.push_back(DB::makecolumname(*ManyToMany<OWNER,RELATED>::default_connection,ManyToMany<OWNER,RELATED>::_related,column)+" ASC");
        return *this;
    }

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::orderBy(std::string&& column,const char order)
    {
        if( order == op::desc)
            order_by.push_back(DB::makecolumname(*ManyToMany<OWNER,RELATED>::default_connection,ManyToMany<OWNER,RELATED>::_related,column)+" DESC");
        else
            order_by.push_back(DB::makecolumname(*ManyToMany<OWNER,RELATED>::default_connection,ManyToMany<OWNER,RELATED>::_related,column)+" ASC");
        return *this;
    }


    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::limit(const unsigned int& count)
    {
        limit_count = static_cast<int>(count);
        return *this;
    };

    template <typename OWNER, typename RELATED>
    M2MQuerySet<OWNER,RELATED>& M2MQuerySet<OWNER,RELATED>::limit(const unsigned int& skip,const unsigned int& count)
    {
        limit_skip = static_cast<int>(skip);
        limit_count = static_cast<int>(count);
        return *this;
    }   


    template <typename OWNER, typename RELATED>
    int M2MQuerySet<OWNER,RELATED>::get(typename std::list<std::shared_ptr<RELATED>>& objs,int max_depth)
    {
        Query* q = makeQuery(max_depth);
        int res = q->getObj(objs,max_depth);
        delete q;
        return res;
    }

    template <typename OWNER, typename RELATED>
    void M2MQuerySet<OWNER,RELATED>::__print__() const
    {
        std::string q_str ="SELECT ";
        ManyToMany<OWNER,RELATED>::nameAttrs(q_str,ORM_DEFAULT_MAX_DEPTH,db);

        q_str+="\nFROM ";
        ManyToMany<OWNER,RELATED>::nameTables(q_str,ORM_DEFAULT_MAX_DEPTH,db);

        const int filters_size = filters.size();

        if(filters_size > 0)
        {
            q_str+=" \nWHERE (";
            auto begin = filters.begin();
            const auto& end = filters.end();
            std::cout<<q_str;
            q_str.clear();

            begin->__print__(*ManyToMany<OWNER,RELATED>::default_connection);

            while(++begin != end)
            {
                std::cout<<" AND ";
                begin->__print__(*ManyToMany<OWNER,RELATED>::default_connection);
            }
            std::cout<<") ";
        }
        
        int _size = order_by.size();
        if(_size >0)
        {
            std::cout<<" ORDER BY ";
            auto begin = order_by.begin();
            const auto& end = order_by.end();
            std::cout<<*begin;

            while(++begin != end)
            {
                std::cout<<" ,"<<*begin;
            }
        }

        if(limit_count > 0)
            std::cout<<db.limit(limit_skip,limit_count);
    };

    template <typename OWNER, typename RELATED>
    Query* M2MQuerySet<OWNER,RELATED>::makeQuery(int max_depth)
    {
        std::string q_str ="SELECT ";
        ManyToMany<OWNER,RELATED>::nameAttrs(q_str,max_depth,db);

        q_str+="\nFROM ";
        ManyToMany<OWNER,RELATED>::nameTables(q_str,max_depth,db);

        const int filters_size = filters.size();

        if(filters_size > 0)
        {
            q_str+=" \nWHERE (";
            auto begin = filters.begin();
            const auto& end = filters.end();

            begin->toQuery(q_str,db);

            while(++begin != end)
            {
                q_str+=" AND ";
                begin->toQuery(q_str,db);
            }
            q_str+=") ";
        }
        
        int _size = order_by.size();
        if(_size >0)
        {
            q_str+=" ORDER BY ";
            auto begin = order_by.begin();
            const auto& end = order_by.end();
            q_str+= (*begin);

            while(++begin != end)
            {
                q_str+=" ,"+(*begin);
            }

        }

        if(limit_count > 0)
            q_str+= db.limit(limit_skip,limit_count);

        Query* q = db.prepareQuery(q_str);
        
        if(filters_size > 0)
        {
            auto begin = filters.begin();
            const auto& end = filters.end();
            unsigned int index = 1;
            while(begin != end)
            {

                begin->set(q,index);
                ++begin;
                ++index;
            }
        }

        return q;
    }
}
