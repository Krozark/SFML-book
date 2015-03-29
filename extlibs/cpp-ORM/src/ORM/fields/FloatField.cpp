#include <ORM/fields/FloatField.hpp>

#include <ORM/backends/DB.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    FloatField::FloatField(const float& value,const std::string& column) : Attr(value,column)
    {
    }

    FloatField::FloatField(const std::string& column) : Attr(0,column)
    {
    }
    
    std::string FloatField::create(const DB& db) const
    {
        return db.creator().floatField(column,false);
    }
}
