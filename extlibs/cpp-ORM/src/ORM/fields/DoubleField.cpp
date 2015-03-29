#include <ORM/fields/DoubleField.hpp>

#include <ORM/backends/DB.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    DoubleField::DoubleField(const double& value,const std::string& column) : Attr(value,column)
    {
    }

    DoubleField::DoubleField(const std::string& column) : Attr(0,column)
    {
    }
    
    std::string DoubleField::create(const DB& db) const
    {
        return db.creator().doubleField(column,false);
    }
}
