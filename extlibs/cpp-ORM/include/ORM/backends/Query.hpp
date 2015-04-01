#ifndef ORM_QUERY_HPP
#define ORM_QUERY_HPP

#include <ORM/backends/DB.hpp>

#include <string>
#include <ostream>
#include <memory>

namespace orm
{

    /**
     * \brief Abstract class to manage query
     **/
    class Query
    {
        public:
             /**
             * \brief Destructor
             **/
            virtual ~Query();

        protected:
            friend class DB;
            friend class MySqlDB;
            friend class Sqlite3DB;
            friend class SqlObjectBase;
            template<typename T> friend class Attr;
            template<typename T> friend class FKBase;
            template<typename T> friend class QuerySet;
            template<typename T> friend class SqlObject;
            template<typename T> friend class Cache;
            template<typename RELATED,typename T> friend class Filter;
            template<typename T,typename U> friend class ManyToMany;
            template<typename T,typename U> friend class M2MQuerySet;

            /**
             * \brief Create a query
             *
             * \param db database where the query will be execute
             * \param query Query string to execute
             **/
            Query(DB& db,const std::string& query);

            /**
             * \brief Create a query
             *
             * \param db database where the query will be execute
             * \param query Query string to execute
             **/
            Query(DB& db,std::string&& query);

            Query(const Query&) = delete;
            Query& operator=(const Query&) = delete;


            /**
             * \brief Count the number of object returned by the batabase
             *
             * \return  The number of objects
             **/
            virtual int count()const = 0;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column the extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(bool& value,const int& column)const = 0;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(int& value,const int& column)const = 0;


            /**
             * \brief Get a value of a PK/FK collumn, and stor it
             *
             * \param value : where the value is stored (<=0 if null)
             * \param colun The column to extract
             *
             * \return false if fail or column is null
             */
            virtual bool getPk(int& value, const int& column)const=0;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(unsigned int& value,const int& column)const = 0;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long long int& value,const int& column)const = 0;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long long unsigned int& value,const int& column)const = 0;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(float& value,const int& column)const = 0;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(double& value,const int& column)const = 0;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long double& value,const int& column)const = 0;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(std::string& value,const int& column)const = 0;

            /**
             * \brief Get a value of a column, and store it
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(struct tm& value,const int& column)const=0;


            /**
             * \brief Construct objects from the query. T must be a SqlObject
             *
             * \param obj Where the object will be stored
             * \param max_depth The maximum recursion depth of object construction (for FK)
             *
             * \return the number of object created
             **/
            template<typename T>
            int getObj(T& obj,int max_depth);

            /**
             * \brief Construct objects from the query. T must be a SqlObject
             *
             * \param objs Where the objects will be stored
             * \param max_depth The maximum recursion depth of object construction (for FK)
             *
             * \return the number of object created
             **/
            template<typename T>
            int getObj(std::vector<std::shared_ptr<T>>& objs,int max_depth);

            /**
             * \brief Print the content of the query for debug help
             **/
            friend std::ostream& operator<<(std::ostream& output,const Query* self)
            {
                output<<self->query;
                return output;
            };

            /**
             * \brief Whene the query have been execute, for loop in results
             *
             * \results fals if fail
             **/
            virtual bool next() = 0;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const bool& value,const unsigned int& column) = 0;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const int& value,const unsigned int& column) = 0;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const unsigned int& value,const unsigned int& column) = 0;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long long int& value,const unsigned int& column) = 0;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long long unsigned int& value,const unsigned int& column) = 0;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const float& value,const unsigned int& column) = 0;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const double& value,const unsigned int& column) = 0;

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long double& value,const unsigned int& column) = 0;

            /**
             *
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const std::string& value,const unsigned int& column) = 0;

            /**
             *
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const struct tm& value, const unsigned int& column)=0;

            /**
             * \brief For prepared query only, set the column value to null
             *
             * \param value Not use. Allow overload only
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool setNull(const int& value,const unsigned int& column) = 0;

            /**
             * \brief Allow subclass to custom the execute function by adding code
             **/
            virtual void executeQuery() = 0;

            bool prepared; ///< is the query is a prepared one?
            std::string query; ///<query as string
            DB& db; ///< database where the query will be executed


        private:
            /**
             * \brief Execute the query on the database
             *
             * \return false if fail
             **/
            void execute();

            bool executed; ///< is the query already executed?
    };
};
#include <ORM/backends/Query.tpl>

#endif
