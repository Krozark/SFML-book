#ifndef ORM_REGISTER_HPP
#define ORM_REGISTER_HPP

#include <ORM/debug.hpp>
#include <ORM/core/Tables.hpp>

namespace orm
{
    /**
    * \brief class to register column name as static (Hack)
    **/
    template<typename T>
    class Register
    {
        public:
            /**
            * \brief constructor. Create a default object, and use it to get attrs, and fk of the class.
            * Note : default constructor have to be anable (without params)
            */
            Register();
    };
}
#include <ORM/core/Register.tpl>

#endif
