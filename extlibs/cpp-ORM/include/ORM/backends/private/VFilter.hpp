#ifndef ORM_VFILTER_HPP
#define ORM_VFILTER_HPP

#include <string>

namespace orm
{
    class Query;
    class DB;

    /**
     * \brief A class representing filter in query
     **/
    class VFilter
    {
        public:
            /**
             * \brief Print the content of the filter for debug help
             **/
            virtual void __print__(const DB& db) const = 0;

            virtual ~VFilter();


        protected:
            //template<typename T> friend class SqlObject;
            template<typename T> friend class QuerySet;
            template<typename T,typename U> friend class M2MQuerySet;
            template<typename T> friend class FilterSet;

            /**
             * \brief Make a copy of the object
             */
            virtual VFilter* clone()const = 0;


           /**
            * \brief set the value in the filter in the query
            *
            * \param query Prepared query
            * \param column column index
            *
            * \return false if fail
            **/
            virtual bool set(Query* query,unsigned int& column) const = 0;

            virtual void toQuery(std::string& query,orm::DB& db) const = 0;
    };
};

#endif

/**
 * \class orm::Filter
 * \ingroup backends
 *
 * orm::Filter is a simple class to represent
 * any filter in a query. It can be use as parameter
 * for filter() and exclude() funtions.
 *
 * Usage Exemple:
 * \code
 * orm::Filter(42,"lt",Player::_lvl)
 * \endcode
 *
 * Note : ope is a operator define in DB class.
 * \see DB::operators
 **/

