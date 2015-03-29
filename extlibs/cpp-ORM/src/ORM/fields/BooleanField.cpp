#include <ORM/fields/BooleanField.hpp>

#include <ORM/backends/DB.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    BooleanField::BooleanField(const bool& value,const std::string& column) : Attr(value,column)
    {
    }

    BooleanField::BooleanField(const std::string& column) : Attr(false,column)
    {
    }
    
    std::string BooleanField::create(const DB& db) const
    {
        return db.creator().booleanField(column,false);
    }
}
