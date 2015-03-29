#include <ORM/models/SqlObjectBase.hpp>
#include <ORM/fields/private/VAttr.hpp>
#include <ORM/fields/private/VFK.hpp>
#include <ORM/backends/Query.hpp>

namespace orm
{
    SqlObjectBase::SqlObjectBase() : pk(-1){}; 

    SqlObjectBase::~SqlObjectBase(){}

    int SqlObjectBase::getPk()const
    {
        return pk;
    }

    void SqlObjectBase::before_save(){}

    void SqlObjectBase::after_save(){}

    void SqlObjectBase::before_update(){}

    void SqlObjectBase::after_update(){}

    void SqlObjectBase::before_load(){};

    void SqlObjectBase::after_load(){};

    bool SqlObjectBase::loadFromDB(const Query& query,int max_depth)
    {
        int prefix=query.db.getInitialGetcolumnNumber() -1;
        return loadFromDB(query,prefix,max_depth);
    };

    bool SqlObjectBase::loadFromDB(const Query& query,int& prefix,int max_depth)
    {
        ++prefix;

        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        std::cerr<<MAGENTA<<"[ATTR] get attr("<<prefix<<") : id"<<BLANC<<std::endl;
        #endif

        bool res = query.get(pk,prefix); //id


        #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
        if(not res)
            std::cerr<<ROUGE<<"[ATTR] get attr("<<prefix<<") : id"<<" fail"<<BLANC<<std::endl;
        #endif
        before_load();
        for(VAttr* attr: attrs)
        {
            ++prefix;
            #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
            std::cerr<<MAGENTA<<"[ATTR] get attr("<<prefix<<") : "<<attr->getcolumn()<<BLANC<<std::endl;
            #endif

            bool tmp = attr->get(query,prefix,max_depth); //incrementation of column number for the next

            #if ORM_DEBUG & ORM_DEBUG_GET_ATTR
            if(not tmp)
                std::cerr<<ROUGE<<"[ATTR] get attr("<<prefix<<") : "<<attr->getcolumn()<<" fail"<<BLANC<<std::endl;
            #endif
            res = (res and  tmp);
        }
        after_load();

        #if ORM_DEBUG & ORM_DEBUG_GET_OBJ
        if(not res)
        {
            std::cerr<<ROUGE<<"[GET OBJ] SqlObjectBase::loadFromDB(const Query& query,int & prefix,int max_depth) failed : One or more attr not get"<<BLANC<<std::endl;
        }
        #endif
        return res;
    };


    std::ostream& operator<<(std::ostream& output,const SqlObjectBase& self)
    {
        output<<"{ \"pk\":"<<self.pk;
        for(VAttr* attr: self.attrs)
            output<<", \""<<attr->getcolumn()<<"\":"<<*attr;
        output<<"}";
        return output;
    };
};
