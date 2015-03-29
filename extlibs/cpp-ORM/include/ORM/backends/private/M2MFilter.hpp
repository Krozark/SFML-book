#ifndef ORM_M2MFILTER_HPP
#define ORM_M2MFILTER_HPP

#include <ORM/backends/private/VFilter.hpp>

namespace orm
{
    template<typename RELATED,typename OWNER,typename T>
    class M2MFilter : public VFilter
    {
        public:

            template<typename ... Args>
            M2MFilter(const T& value,const std::string& ope,const std::string& column,Args&& ... args);

            virtual ~M2MFilter();

            /**
             * \brief Print the content of the filter for debug help
             **/
            virtual void __print__(const DB& db) const final;

        private:
            const std::string column; ///< Colum to apply filter
            const std::string ope; ///< operator to use. \see DB::operators
            const T value; ///< Store the value of the filter to compare with
            
            virtual VFilter* clone() const;
            
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
#include <ORM/backends/private/M2MFilter.tpl>
#endif
