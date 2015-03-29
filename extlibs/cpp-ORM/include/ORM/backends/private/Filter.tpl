#include <sstream>
#include <ctime>
#include <cstring>

#include <ORM/fields/DateTimeField.hpp>

namespace orm
{
    //default do nothing
    template<typename T>
    T __filter_value_helper(const T& value)
    {
        return value;
    }

    //special date type
    template<>
    struct tm __filter_value_helper<struct tm>(const struct tm& value);

    template<typename RELATED,typename T>
    template<typename ... Args>
    Filter<RELATED,T>::Filter(const T& val,const std::string& ope,const std::string& column,Args&& ... args) : column(DB::makecolumname(*RELATED::default_connection,RELATED::table,column,std::forward<Args>(args)...)), ope(ope), value(__filter_value_helper(val))
    {
    };

    template<typename RELATED,typename T>
    Filter<RELATED,T>::Filter(Filter<RELATED,T>&& other) : column(std::move(other.column)), ope(std::move(other.ope)), value(other.value)
    {
    }

    template<typename RELATED,typename T>
    Filter<RELATED,T>::~Filter()
    {
    };


    template<typename RELATED,typename T>
    void Filter<RELATED,T>::__print__(const DB& db) const
    {
        const std::string& op = db.operators.at(ope);

        std::string v;
        {
            std::stringstream ss;
            ss<<value;
            v=ss.str();
        }

        char buffer[ope.size() + v.size()];
        sprintf(buffer,op.c_str(),v.c_str());

        std::cout<<column<<" "<<buffer;
        //DB::makecolumname(db,OBJ::table,column,args...)
    };

    //default do nothing
    template<typename T>
    T __filter_clone_helper(const T& value)
    {
        return value;
    }

    //special date type
    template<>
    struct tm __filter_clone_helper<struct tm>(const struct tm& value);

    template<typename RELATED,typename T>
    VFilter* Filter<RELATED,T>::clone() const
    {
        return new Filter<RELATED,T>(__filter_clone_helper(value),ope,column);
    };

    template<typename RELATED,typename T>
    bool Filter<RELATED,T>::set(Query* query,unsigned int& column) const
    {
        auto v = query->db.formatValue(ope,value);

        bool res = query->set(v,column);
        #if ORM_DEBUG & ORM_DEBUG_SQL
        if (not res)
            std::cerr<<ROUGE<<"[ERROR][Sql:makeQuery] Impossible to bind values <"<<v<<"> on colum "<<column<<BLANC;
        #endif
        return res;

    }

    template<typename RELATED,typename T>
    void Filter<RELATED,T>::toQuery(std::string& query,DB& db) const
    {
        query += column + db.formatPreparedValue(ope);
    }
}
