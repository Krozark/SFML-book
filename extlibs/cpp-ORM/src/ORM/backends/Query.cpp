#include <algorithm>

#include <ORM/backends/Query.hpp>


namespace orm
{
    Query::Query(DB& b,const std::string& q) :prepared(false), query(q), db(b), executed(false)
    {
    };

    Query::Query(DB& b,std::string&& q) : prepared(false), db(b), executed(false)
    {
        std::swap(q,query);
    };

    Query::~Query()
    {
    }

    void Query::execute()
    {
        #if (ORM_DEBUG & ORM_DEBUG_SQL)
        std::cerr<<VERT<<"[Sql] Query::execute()"<<query<<BLANC<<std::endl;
        #endif
        
        executed = true;
        if(not prepared)
        {
            query+=";";
        }
        executeQuery();
    };

};
