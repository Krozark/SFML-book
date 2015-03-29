#ifndef ORM_FILTERSET_HPP
#define ORM_FILTERSET_HPP

//#include <ORM/backends/private/VFilter.hpp>
#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    template<typename RELATED>
    class FilterSet
    {
        public:

            FilterSet(FilterSet<RELATED>&& a);
            FilterSet(const FilterSet<RELATED>& a);

            template<typename T>
            FilterSet(Filter<RELATED,T>&& f);

            FilterSet(FilterSet<RELATED>&& l, const std::string& o);
            FilterSet(const FilterSet<RELATED>& l, const std::string& o);

            FilterSet(FilterSet<RELATED>&& l, const std::string o,FilterSet<RELATED>&& r);

            ~FilterSet();

            void __print__(const DB& db)const;


        private:
            void* left;
            std::string ope;
            FilterSet<RELATED>* right;


            enum Type {
                LEAF,
                UNARY,
                BINARY,
            } type;
            
        protected:
            template<typename T> friend class QuerySet;
            template<typename T,typename U> friend class M2MQuerySet;
           /**
            * \brief set the value in the filter in the query
            *
            * \param query Prepared query
            * \param column column index
            *
            * \return false if fail
            **/
            bool set(Query* query,unsigned int& column) const;

            /**
             * \brief add the sql code to the query
             * \param query sql to append to
             * \param db data base to use
             */
            void toQuery(std::string& query,DB& db) const;
    };

    template<typename RELATED>
    FilterSet<RELATED> operator!(FilterSet<RELATED>&& a);

    template<typename RELATED>
    FilterSet<RELATED> operator!(const FilterSet<RELATED>& a);

    template<typename RELATED>
    FilterSet<RELATED> operator&&(FilterSet<RELATED>&& a, FilterSet<RELATED>&& b);

    template<typename RELATED>
    FilterSet<RELATED> operator||(FilterSet<RELATED>&& a, FilterSet<RELATED>&& b);
    
    template <typename RELATED,typename T, typename ... Args>
    FilterSet<RELATED> Q(const T& value,Args&& ... args);

}
#include <ORM/backends/private/FilterSet.tpl>
#endif
