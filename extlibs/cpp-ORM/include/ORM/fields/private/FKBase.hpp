#ifndef ORM_FKBASE_HPP
#define ORM_FKBASE_HPP

#include <ORM/fields/private/VFK.hpp>
#include <memory>

namespace orm
{
    class Query;
    template<typename T> class Cache;

    /**
     * \brief Store a FK to a object
     **/
    template<typename T>
    class FKBase : public VFK
    {
        public:
            FKBase(const FKBase&) = delete;

            /**
             * \brief Destructor
             **/
            ~FKBase();


            /**
             * \brief Save or update the object on the fk
             *
             * \param db the db to fetch
             * \param recursive save recursively
             *
             * \return false if fail
             **/
            virtual bool save(bool recursive=false,DB& db=*T::default_connection) override;

            /**
             * \brief Delete the object from the db and cache
             *  
             *  Note : whe use on object linked in other object with fks can cause trouble because of the remove of the cache
             *  Set the pk to -1
             * \param db the db to fetch
             *
             * \return fale if fail
             **/
            virtual bool del(bool recursive=false,DB& db=*T::default_connection) override;

            typedef T type; ///< Type of stored object

            /**
             * \brief assessor operator to the stored object
             **/
            typename T::type_ptr operator->();

            /**
             * \brief cast operator
             *
             * \cast this in value
             **/
            T& operator*();

            /**
             * \brief convertion operator
             */
            operator typename T::type_ptr() const;

            /**
             * \brief Test if a value is stared
             */
            explicit operator bool()const;

            /**
             * \brief Copy operator
             **/
            FKBase<T>& operator=(const FKBase<T>& other);

            /**
             * \brief Copy operator
             **/
            FKBase<T>& operator=(const typename Cache<T>::type_ptr& other);

            virtual std::ostream& print_value(std::ostream& output)const;

            virtual bool test() const override;

        protected:
            /**
             * \brief Construct a FK
             *
             * \param column Column where the object fk is stored
             * \param nullable if the fk can be null
             **/
            FKBase(const std::string& column,const bool nullable=true);

            typename T::type_ptr value_ptr; ///< the stored object

            /**
             * \brief Set the fk value to the query
             *
             * \param query the prepared query
             * \param column the column number of the table
             *
             * \return false if fail
             **/
            virtual bool set(Query& query,const unsigned int& column);

            /**
             * \brief get the fk from the query
             *
             * \param query the executed query
             * \param prefix the column number
             * \param max_depth the maximun recursion of construction
             *
             * \return false if fail
             **/
            virtual bool get(const Query& query,int& prefix,int max_depth);

            /**
             * \brief Construct a new object from the db
             *
             * \param db the db to fetch
             * \param max_depth maximun depth of construction
             *
             * \return The new object
             **/
            void setObjectT_ptr(DB& db,int max_depth = ORM_DEFAULT_MAX_DEPTH);

            /**
             * \brief make the attrs colum name
             *
             * \param db db use for the query
             * \param prefix prefix table alias for linked object
             * \param max_depth maximun depth of construction
             *
             * \return the columns alias
             **/
            virtual std::string makeName(DB& db,const std::string& prefix,int max_depth) const;

            /**
             * \brief Use for increment the column number without construction.
             * Note : this is use with the cache if the object is find in it
             *
             * \param depth column nuber to increment
             * \param max_depth maximun depth of construction
             **/
            virtual void incDepth(int& depth,int max_depth) const;

            /**
             * \brief get the stored object
             *
             * \param db the db to fetch
             * \param max_depth maximun depth of construction if object not existe
             *
             * \return the stored object
             **/
            virtual const SqlObjectBase& getObject(DB& db,int max_depth=ORM_DEFAULT_MAX_DEPTH);


            /**
             * \brief create the attr column
             */
            virtual std::string create(const DB& db) const;

    };
}

#include <ORM/fields/private/FKBase.tpl>

#endif
