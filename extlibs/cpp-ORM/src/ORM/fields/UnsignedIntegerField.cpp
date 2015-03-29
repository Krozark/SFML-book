#include <ORM/fields/UnsignedIntegerField.hpp>

#include <ORM/backends/DB.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    UnsignedIntegerField::UnsignedIntegerField(const int& value,const std::string& column) : Attr(value,column)
    {
    }

    UnsignedIntegerField::UnsignedIntegerField(const std::string& column) : Attr(0,column)
    {
    }
    
    std::string UnsignedIntegerField::create(const DB& db) const
    {
        return db.creator().positiveIntegerField(column,false);
    }
}
