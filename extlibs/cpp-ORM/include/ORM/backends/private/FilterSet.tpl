namespace orm
{
    template<typename RELATED>
    template<typename T>
    FilterSet<RELATED>::FilterSet(Filter<RELATED,T>&& f): left(new Filter<RELATED,T>(std::forward<Filter<RELATED,T>>(f))), ope(), right(nullptr), type(LEAF)
    {
    };

    template<typename RELATED>
    FilterSet<RELATED>::FilterSet(FilterSet<RELATED>&& a) : left(nullptr), ope(), right(nullptr), type(a.type)
    {
        std::swap(left,a.left);
        std::swap(ope,a.ope);
        std::swap(right,a.right);
    }

    template<typename RELATED>
    FilterSet<RELATED>::FilterSet(const FilterSet<RELATED>& a) :ope(a.ope), type(a.type)
    {
        switch(type)
        {
            case LEAF:
                left = reinterpret_cast<VFilter*>(a.left)->clone();
                right = nullptr;
                break;
            case UNARY:
                left = new FilterSet<RELATED>(*reinterpret_cast<FilterSet<RELATED>*>(a.left));
                right = nullptr;
                break;
            case BINARY:
                left = new FilterSet<RELATED>(*reinterpret_cast<FilterSet<RELATED>*>(a.left));
                right = new FilterSet<RELATED>(*a.right);
                break;
        }
    }

    template<typename RELATED>
    FilterSet<RELATED>::FilterSet(FilterSet<RELATED>&& l, const std::string& o) : left(new FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(l))), ope(o), right(nullptr), type(UNARY)
    {
    }

    template<typename RELATED>
    FilterSet<RELATED>::FilterSet(const FilterSet<RELATED>& l, const std::string& o) : left(new FilterSet<RELATED>(l)), ope(o), right(nullptr), type(UNARY)
    {
    }

    template<typename RELATED>
    FilterSet<RELATED>::FilterSet(FilterSet<RELATED>&& l, const std::string o,FilterSet<RELATED>&& r) : left(new FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(l))), ope(o), right(new FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(r))), type(BINARY)
    {
    }

    template<typename RELATED>
    FilterSet<RELATED>::~FilterSet()
    {
        if(type == LEAF)
            delete reinterpret_cast<VFilter*>(left);
        else
        {
            delete reinterpret_cast<FilterSet<RELATED>*>(left);
            delete right;
        }
    }

    template<typename RELATED>
    void FilterSet<RELATED>::__print__(const DB& db)const
    {
        switch(type)
        {
            case LEAF:
            {
                reinterpret_cast<VFilter*>(left)->__print__(db);
            }break;
            case UNARY:
            {
                std::cout<<"("<<ope<<" ";
                reinterpret_cast<FilterSet<RELATED>*>(left)->__print__(db);
                std::cout<<")";
            }break;
            case BINARY:
            {
                std::cout<<"(";
                reinterpret_cast<const FilterSet<RELATED>*>(left)->__print__(db);
                std::cout<<" "<<ope<<" ";
                right->__print__(db);
                std::cout<<")";
            }break;
        }
    }


    template<typename RELATED>
    bool FilterSet<RELATED>::set(Query* query,unsigned int& column) const
    {
        bool res = false;
        switch (type)
        {
            case LEAF :
                res = reinterpret_cast<VFilter*>(left)->set(query,column);
                break;
            case UNARY:
                res = reinterpret_cast<FilterSet*>(left)->set(query,column);
                break;
            case BINARY:
                res = reinterpret_cast<FilterSet<RELATED>*>(left)->set(query,column);
                ++column;
                res= res and right->set(query,column);
                break;
            default:
                break;
        }
        return res;
    }

    template<typename RELATED>
    void FilterSet<RELATED>::toQuery(std::string& query,DB& db) const
    {
        switch (type)
        {
            case LEAF :
                reinterpret_cast<VFilter*>(left)->toQuery(query,db);
                break;
            case UNARY:
                query+="("+ope+" ";
                reinterpret_cast<FilterSet<RELATED>*>(left)->toQuery(query,db); 
                query+=")";
                break;
            case BINARY:
                query+="(";
                reinterpret_cast<FilterSet<RELATED>*>(left)->toQuery(query,db);
                query+=" "+ope+" ";
                right->toQuery(query,db); 
                query+=")";
                break;
            default:
                break;
        }
    }

    
    template<typename RELATED>
    FilterSet<RELATED> operator!(FilterSet<RELATED>&& f)
    {
        return FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(f),"NOT");
    }

    template<typename RELATED>
    FilterSet<RELATED> operator!(const FilterSet<RELATED>& f)
    {
        return FilterSet<RELATED>(f,"NOT");
    }

    template<typename RELATED>
    FilterSet<RELATED> operator&&(FilterSet<RELATED>&& a,FilterSet<RELATED>&& b)
    {
        return FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(a),"AND",std::forward<FilterSet<RELATED>>(b));
    }

    template<typename RELATED>
    FilterSet<RELATED> operator||(FilterSet<RELATED>&& a,FilterSet<RELATED>&& b)
    {
        return FilterSet<RELATED>(std::forward<FilterSet<RELATED>>(a),"OR",std::forward<FilterSet<RELATED>>(b));
    }

    template <typename RELATED,typename T, typename ... Args>
    FilterSet<RELATED> Q(const T& value,Args&& ... args)
    {
        Filter<RELATED,T> tmp(value,std::forward<Args>(args)...);
        return FilterSet<RELATED>(std::move(tmp));
    }
}
