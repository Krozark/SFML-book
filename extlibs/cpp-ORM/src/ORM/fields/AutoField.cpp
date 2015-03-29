#include <ORM/fields/AutoField.hpp>

#include <ORM/backends/DB.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    AutoField::AutoField(const int& value,const std::string& column) : Attr(value,column)
    {
    }

    AutoField::AutoField(const std::string& column) : Attr(-1,column)
    {
    }
    
    std::string AutoField::create(const DB& db) const
    {
        return db.creator().autoField(column);
    }
}
