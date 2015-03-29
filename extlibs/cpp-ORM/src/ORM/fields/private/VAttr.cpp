#include <ORM/fields/private/VAttr.hpp>
#include <ORM/models/SqlObjectBase.hpp>
#include <ORM/backends/DB.hpp>

namespace orm 
{
    VAttr::VAttr(const std::string& col) : modify(false), column(col)
    {
    };

    VAttr::~VAttr()
    {
    }

    std::ostream& operator<<(std::ostream& output,const VAttr& self)
    {
        return self.print_value(output);
    };
    const std::string& VAttr::getcolumn() const
    {
        return column;
    }
    
    void VAttr::registerAttr(SqlObjectBase& object)
    {
        object.attrs.emplace_back(this);
    }

    void VAttr::before_save(){}

    void VAttr::after_save(){}

    void VAttr::before_update(){}

    void VAttr::after_update(){}

    std::string VAttr::makeName(DB& db, const std::string& prefix,int max_depth) const
    {
        return ", "+db.escapeColumn(prefix)+"."+db.escapeColumn(column)+" AS "+JOIN_ALIAS(prefix,column);
    }

};
