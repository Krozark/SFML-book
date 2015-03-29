#ifndef ORM_FILTER_HPP
#define ORM_FILTER_HPP

#include <ORM/backends/private/VFilter.hpp>
#include <ORM/backends/Query.hpp>

namespace orm
{
    /**
     * \brief A class to build filters
     * T have to be a primitiv type (char, bool,int, float, double, unsigned, long, long long)
     **/
    template<typename RELATED,typename T>
    class Filter : public VFilter
    {
        public:

            Filter(const Filter<RELATED,T>&)=delete;
            Filter& operator=(const Filter<RELATED,T>&) = delete;

            Filter(Filter<RELATED,T>&&);
            Filter& operator=(Filter<RELATED,T>&&) = delete;

            /**
             * \brief Create a filter
             *
             * \param column column where the filter will be apply
             * \param ope Operator to apply
             * \param value Value to compare
             **/
            template<typename ... Args>
            Filter(const T& value,const std::string& ope,const std::string& column,Args&& ... args);

            virtual ~Filter();

            /**
             * \brief Print the content of the filter for debug help
             **/
            virtual void __print__(const DB& db) const final;

        //protected:
            const std::string column; ///< Colum to apply filter
            const std::string ope; ///< operator to use. \see DB::operators
            const T value; ///< Store the value of the filter to compare with


            virtual VFilter* clone() const final;

           /**
            * \brief set the value in the filter in the query
            *
            * \param query Prepared query
            * \param column column index
            *
            * \return false if fail
            **/
            virtual bool set(Query* query,unsigned int& column) const final;

            /**
             * \brief add the sql code to the query
             * \param query sql to append to
             * \param db data base to use
             */
            virtual void toQuery(std::string& query,DB& db) const final;
    };
}
#include <ORM/backends/private/Filter.tpl>
#endif
