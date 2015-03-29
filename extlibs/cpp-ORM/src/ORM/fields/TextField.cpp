#include <ORM/fields/TextField.hpp>

#include <ORM/backends/DB.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    
    TextField::TextField(const std::string& value,const std::string& column) : Attr(value,column)
    {
    }

    TextField::TextField(const std::string& column) : Attr("",column)
    {
    }
    
    std::string TextField::create(const DB& db) const
    {
        return db.creator().textField(column,false);
    }
}
