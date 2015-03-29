#ifndef ORM_EXTERNALS_HPP
#define ORM_EXTERNALS_HPP

#include <ORM/debug.hpp>

#include <iostream>

namespace orm
{
    static const std::string TABLE_ALIAS_SEPARATOR("__"); ///< table separator in sql alias constructionh

    /**
     * \brief make a new alias using 2 tables names / alias
     *
     * \param prefix The fist table alias/name
     * \param column the other table name to concat
     *
     * \return the column alias
     **/
    static inline const std::string JOIN_ALIAS(const std::string& prefix,const std::string& column)
    {
        return prefix+TABLE_ALIAS_SEPARATOR+column;
    };


    /**
     * \brief Like JOIN_ALIAS but, make no change if prefix is empty
     *
     * \param prefix The fist table alias/name
     * \param column the other table name to concat
     *
     * \return the column alias
     **/
    static inline const std::string MAKE_PREFIX(const std::string& prefix,const std::string& table)
    {
        return (prefix.size()>0)?JOIN_ALIAS(prefix,table):table;
    };
}
#endif
