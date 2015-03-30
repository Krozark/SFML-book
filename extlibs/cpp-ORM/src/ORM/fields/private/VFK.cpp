#include <ORM/fields/private/VFK.hpp>
#include <ORM/models/SqlObjectBase.hpp>

namespace orm
{
    VFK::VFK(const std::string& column,bool nullable) : VAttr(column) , fk(-1), nullable(nullable)
    {
    }

    void VFK::registerAttr(SqlObjectBase& object)
    {
        object.attrs.emplace_back(this);
        object.fks.emplace_back(this);
    }

};
