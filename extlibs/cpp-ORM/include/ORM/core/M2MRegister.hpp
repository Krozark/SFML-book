#ifndef ORM_M2MREGISTER_HPP
#define ORM_M2MREGISTER_HPP

#include <ORM/debug.hpp>
#include <ORM/core/Tables.hpp>

namespace orm
{
    /**
    * \brief class to register column name as static (Hack)
    **/
    template<typename OWNER,typename RELATED>
    class M2MRegister
    {
        public:
            /**
            * \brief constructor. Create a default object, and use it to get attrs, and fk of the class.
            * Note : default constructor have to be anable (without params)
            */
            M2MRegister();
    };
}
#include <ORM/core/M2MRegister.tpl>

#endif
