#ifndef ORM_M2MQUERYSET_HPP
#define ORM_M2MQUERYSET_HPP

#include <ORM/backends/private/VFilter.hpp>
#include <ORM/core/Cache.hpp>
#include <ORM/backends/op.hpp>
#include <memory>
#include <list>

namespace orm
{
    template<typename T,typename U> class ManyToMany;
    /**
     * \brief A class that allow you to make query on the type T
     *
     * Note : T must be a SqlObject
     *
     * \see SqlObject
     **/
    template <typename OWNER, typename RELATED>
    class M2MQuerySet
    {
        public:

            M2MQuerySet(M2MQuerySet&&) = default;
            M2MQuerySet& operator=(M2MQuerySet&&) = default;


            /**
             * \brief Destructor
             **/
            ~M2MQuerySet();

            /**
             * \brief Construct a filter to apply in the query
             *
             * \param value The value to compare with
             * \param The operator to use see DB::Operators for detail
             * \param column The column to apply the comparasion
             * \param args If more than one collum is send, all column will be concatenate (with the correct format) to create the correct column name. Args must be std::string
             * \return *this
             **/
            template<typename T,typename ... Args>
            M2MQuerySet<OWNER,RELATED>& filter(T&&,const std::string& op,Args&& ... args);

            M2MQuerySet<OWNER,RELATED>& filter(const FilterSet<ManyToMany<OWNER,RELATED>>& f);
            M2MQuerySet<OWNER,RELATED>& filter(FilterSet<ManyToMany<OWNER,RELATED>>&&);

            /**
             * \brief Add a order by constrait to the query
             *
             * \param column The column to use for ordering
             * \param oder The column ordering ( +=ASC or -=DESC)
             *
             * \return *this;
             **/
            M2MQuerySet<OWNER,RELATED>& orderBy(const std::string& column,const char order=op::asc);

            /**
             * \brief Add a order by constrait to the query
             *
             * \param column The column to use for ordering
             * \param oder The column ordering ( +=ASC or -=DESC)
             *
             * \return *this;
             **/
            M2MQuerySet<OWNER,RELATED>& orderBy(std::string&& column,const char order=op::asc);
            //M2MQuerySet& orderBy(int,const std::string& column);

            /**
             * \brief Add a negatide filter to the query
             *
             * \param value The value to compare with
             * \param The operator to use see DB::Operators for detail
             * \param column The column to apply the comparasion
             * \param args If more than one collum is send, all column will be concatenate (with the correct format) to create the correct column name. Args must be std::string
             *
             * \return *this
             **/
            template<typename U,typename ... Args>
            M2MQuerySet<OWNER,RELATED>& exclude(const U& value,const std::string& operande,const std::string& column,const Args& ... args);

            /**
             * \brief Add a limit of the number of object return by the dbtabase
             *
             * \param count Maximun number of object
             *
             * \return *this
             **/
            M2MQuerySet<OWNER,RELATED>& limit(const unsigned int& count);

            /**
             * \brief Add a limit of the number of object return by the dbtabase.
             *
             * .limit(2,5) will return up to 5 (0~5) objects after the execution of the query.
             *
             * \param skip Skip the first <skipe> objects
             * \param count Maximun range of object to return
             *
             * \return *this
             **/
            M2MQuerySet<OWNER,RELATED>& limit(const unsigned int& skip,const unsigned int& count);

            //M2MQuerySet& aggregate();

            /**
             * \brief Execute tho query and return the list list of objects
             *
             * \param obj Where the results will be stored. The objects are added to the list.
             * \param max_depth the maximun recursion depth for the object construction (for fk)
             *
             * \return Number of objects
             **/
            int get(typename RELATED::result_type& obj,int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
             * \brief Print the content of the filter for debug help
             **/
            void __print__() const;


        private:
            friend class ManyToMany<OWNER,RELATED>;
            /**
             * \brief Construct a empty M2MQuerySet
             **/
            explicit M2MQuerySet(const ManyToMany<OWNER,RELATED>& m2m,DB& db);

            /**
             * \brief Construct the query with all constraints
             *
             * \param max_depth Maximun depth of recursion in join (if object have FK only)
             *
             * \return NULL if fail or the query to use in othe case
             **/
            Query* makeQuery(int max_depth);


            M2MQuerySet(const M2MQuerySet&) = delete;
            M2MQuerySet& operator=(const M2MQuerySet&) = delete;

            std::list<FilterSet<ManyToMany<OWNER,RELATED>>> filters; ///< Store all the filters
            std::vector<std::string> order_by; ///< store the column name for ordering
            int limit_skip, ///< skip limit (default is 0)
                limit_count; ///< skip limit (default is all)
            DB& db;
            const ManyToMany<OWNER,RELATED>& m2m;
    };
}
/***
 * \todo make query like:
 * SELECT SUM(`sort`.`niveau_max`) AS `niveau_max__sum` FROM `sort` WHERE (...)
 * SELECT AVG(`website_sort`.`niveau_max`) AS `niveau_max__avg`, SUM(`website_sort`.`niveau_max`) AS `niveau_max__sum` FROM `website_sort` WHERE (`website_sort`.`passif` = 0  AND `website_sort`.`niveau_max` >= 2 )
 * AVG, SUM, MIN, MAX
 **/
/*template<typename T>
  M2MQuerySet<T>& M2MQuerySet<T>::aggregate()
  {
  std::cerr<<"[todo]: queryset<t>::agregate()"<<std::endl;
  return *this;
  };*/
#include <ORM/backends/private/M2MQuerySet.tpl>
#endif
