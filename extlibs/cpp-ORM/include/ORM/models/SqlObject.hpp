#ifndef ORM_SqlOBJECT_HPP
#define ORM_SqlOBJECT_HPP

//orm::
#include <ORM/models/SqlObjectBase.hpp>
#include <ORM/fields/private/VFK.hpp>
#include <ORM/core/Cache.hpp>
#include <ORM/core/macros.hpp>
#include <ORM/core/Register.hpp>
//std::
#include <memory>


namespace orm
{

    class DB;
    template<typename T> class QuerySet;
    /**
    * \brief a class to manage customs sql objects
    * Note : T is your model
    *
    * Usage : 
    * \code
    * class A : SqlObject<A>
    * { 
    * ...
    * MAKE_STATIC_COLUMN(A,"table_name",...)
    * };
    * \endcode
    **/
    template<typename T>
    class SqlObject : public SqlObjectBase, public std::enable_shared_from_this<T>
    {
        public:
            using result_type = typename QuerySet<T>::result_type;
            using type_ptr = typename Cache<T>::type_ptr;


            SqlObject(const SqlObject&) = delete;
            SqlObject& operator=(const SqlObject&) = delete;
            
            /**
            * \brief make a SqlObject
            **/
            SqlObject();

            template<typename ... Args>
            static type_ptr create(Args&& ... args);

            /**
            * \brief create a new object from query
            *
            * \param query the query row of the object
            * \param prefix column index
            * \param max_depth maximum depth of constrution
            *
            * \return the new object (need to delete it by hand)
            **/
            static type_ptr createFromDB(const Query& query,int& prefix,int max_depth);

            /**
            * \brief shortcut for T::query().filter(id,"exact","id").get(obj)
             * \param db the db to fetch
            * \return the object of pk id
            *
            * Note : if the return obj as a pk of -1 : fail
            **/
            static type_ptr get(const unsigned int& id,DB& db= *default_connection,int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
            * \brief shortcut for T::query().get(list)
             * \param db the db to fetch
            *
            * \return all the objects T
            **/
            static result_type all(DB& db = *default_connection,int max_depth=ORM_DEFAULT_MAX_DEPTH);

            /**
            * \brief create a queryset for the objet. Use it to make your query
             * \param db the db to fetch
            *
            * \return The tempory queryset. use chaine function, or copy it
            **/
            static QuerySet<T> query(DB& db = *default_connection);

            /**
            * \brief save/update the object in data base
            *
             * \param db the db to fetch
            * \param recursive recursive?
            *
            * \return false if fail
            **/
            virtual bool save(bool recursive=false,DB& db = *default_connection) override final;

            /**
            * \brief delete the object from de data base
            *
             * \param db the db to fetch
            * \param recursive recursive?
            * \return false if fail
            **/
            virtual bool del(bool recursive=false,DB& db = *default_connection) override final;


            type_ptr as_type_ptr();


            /**
             * \brief create the table
             * \todo
             * \return true if success
             */
            static bool createTable(DB& db = *default_connection);

            /**
             * \brief drop the table
             * \todo
             * \return true if success
             */
            static bool dropTable(DB& db = *default_connection);

            /**
             * \brief truncate the table
             * \todo
             * \return true if success
             */
            static bool clearTable(DB& db = *default_connection);

            static  DB* default_connection; ///< db use to stor the object

        protected:
            const static std::string table; ///< the table name
            static Cache<T> cache; ///< the cache containing the objects

            /**
            * \return the table name
            **/
            virtual const std::string& getTable()const override {return table;};
            
            /**
             * \brief make the attrs columns alias
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

            /**
             * \brief make the table alias
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

            /**
             * \brief make the table alias of fk with join
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            virtual void _makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db)const override;

        private:

            template<typename U> friend class Cache;
            template<typename U> friend class Register;
            template<typename U,typename V> friend class ManyToMany;
            template<typename RELATED,typename U> friend class Filter;
            friend class FKBase<T>;
            friend class Query;
            friend class QuerySet<T>;

            static Register<T> _register; ///< use to auto register the class
            static std::vector<const VAttr*> column_attrs; ///< attr of the class
            static std::vector<VFK*> column_fks; ///< fk of the class

            /**
            * \brief make the attrs columns alias
            *
             * \param db the db to fetch
            * \param q_str string query to add the alias
            * \param prefix prefix column name
            * \param max_depth maximun depth of constrution
            **/
            static void nameAttrs(std::string& q_str,const std::string& prefix,int max_depth,DB& db);

            /**
             * \brief make the table alias
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            static void nameTables(std::string& q_str,const std::string& prefix,int max_depth,DB& db);

            /**
             * \brief make the table alias of fk with join
             *
             * \param db the db to fetch
             * \param q_str string query to add the alias
             * \param prefix prefix column name
             * \param max_depth maximun depth of constrution
             **/
            static void makeJoin(std::string& q_str,const std::string& prefix,int max_depth,DB& db);


            /**
            * \brief Create a abject of pk id
            *
             * \param db the db to fetch
            * \param id the pk of the object
            * \param max_depth maximun depth of construction
            *
            * \return the objet (delete it by hand)
            **/
            static type_ptr _get_ptr(const unsigned int id,DB& db,int max_depth);

            /**
            * \brief use by the cache to increment depth
            **/
            static void incDepth(int& depth,int max_depth);

    };
};

#include <ORM/models/SqlObject.tpl>
#endif
