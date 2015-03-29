#include <ORM/core/Tables.hpp>

namespace orm
{
    std::vector<bool(*)()> Tables::_create;
    std::vector<bool(*)()> Tables::_drop;
    std::vector<bool(*)()> Tables::_clear;

    int Tables::create()
    {
        int res = 0;
        //TODO beginTransaction
        for(bool(*f)() : _create)
        {
            res += f();
        }
        //TODO commit
        return res;
    }
    
    int Tables::drop()
    {
        int res = 0;
        //TODO beginTransaction
        for(bool(*f)() : _drop)
        {
            res += f();
        }
        //TODO commit
        return res;
    }

    int Tables::clear()
    {
        int res = 0;
        //TODO beginTransaction
        for(bool(*f)() : _clear)
        {
            res += f();
        }
        //TODO commit
        return res;
    }
}
