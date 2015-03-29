#ifndef ORM_MYSqlQUERY_HPP
#define ORM_MYSqlQUERY_HPP

#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#include <ORM/backends/Query.hpp>

namespace orm
{
    class MySqlDB;

    /**
     * \brief Abstract class to manage query with Mysql only
     **/
    class MySqlQuery : public Query
    {
        protected:
            /**
             * \brief Create a query
             *
             * \param db database where the query will be execute
             * \param query Query string to execute
             **/
            MySqlQuery(DB& db,const std::string& query);

            /**
             * \brief Create a query
             *
             * \param db database where the query will be execute
             * \param query Query string to execute
             **/
            MySqlQuery(DB& db,std::string&& query);

            MySqlQuery(const MySqlQuery&) = delete;
            MySqlQuery& operator=(const MySqlQuery&) = delete;
            
            /**
             * \brief Destructor
             **/
            ~MySqlQuery();

            /**
             * \brief Count the number of object returned by the batabase
             *
             * \return  The number of objects
             **/
            virtual int count()const;
            
            /**
             * \brief Get a value of a column, and store it 
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(bool& value,const int& column)const;

            /**
             * \brief Get a value of a column, and store it 
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(int& value,const int& column)const;

            /**
             * \brief Get a value of a PK/FK collumn, and stor it
             *
             * \param value : where the value is stored (<=0 if null)
             * \param colun The column to extract
             *
             * \return false if fail or column is null
             */
            virtual bool getPk(int& value, const int& column)const;

            /**
             * \brief Get a value of a column, and store it 
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(unsigned int& value,const int& column)const;

            /**
             * \brief Get a value of a column, and store it 
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long long int& value,const int& column)const;

            /**
             * \brief Get a value of a column, and store it 
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long long unsigned int& value,const int& column)const;

            /**
             * \brief Get a value of a column, and store it 
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(float& value,const int& column)const;

            /**
             * \brief Get a value of a column, and store it 
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(double& value,const int& column)const;

            /**
             * \brief Get a value of a column, and store it 
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(long double& value,const int& column)const;

            /**
             * \brief Get a value of a column, and store it 
             *
             * \param colun The column to extract
             * \param value Wher the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(std::string& value,const int& column)const;

            /**
             * \brief Get a value of a column, and store it 
             *
             * \param colun The column to extract
             * \param value Where the value will be stored
             *
             * \return false if fail
             **/
            virtual bool get(struct tm& value,const int& column)const;
           
        
            /**
             * \brief Whene the query have been execute, for loop in results
             *
             * \results fals if fail 
             **/
            virtual bool next();

            /* for prepared query */
            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const bool& value,const unsigned int& column);

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const int& value,const unsigned int& column);

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const unsigned int& value,const unsigned int& column);

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long long int& value,const unsigned int& column);

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long long unsigned int& value,const unsigned int& column);
            
            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const float& value,const unsigned int& column);

            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const double& value,const unsigned int& column);
            
            /**
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const long double& value,const unsigned int& column);

            /**
             *
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const std::string& value,const unsigned int& column);
            /**
             *
             * \brief For prepared query only, set the column value
             *
             * \param value The value to set
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool set(const struct tm& value, const unsigned int& colum);
            
            /**
             * \brief For prepared query only, set the column value to null
             *
             * \param value Not use. Allow overload only
             * \param column The column number to set
             *
             * \results false if fail
             **/
            virtual bool setNull(const int& value,const unsigned int& column);

            /**
            * \brief Execute a query
            *
            * \return false if faild
            * */
            virtual void executeQuery();


        private:
            friend class MySqlDB;

            sql::ResultSet  *db_res; ///< Create a pointer to a ResultSet object to hold the results of any queries we run
            sql::PreparedStatement *prepared_statement; ///< Hold the statement
            sql::Statement  *statement; ///< Create a pointer to a Statement object to hold our Sql commands
    };
};
/* sql::DataType (mysql)
 * 	enum {
		UNKNOWN = 0,
		BIT,
		TINYINT,
		SMALLINT,
		MEDIUMINT,
		INTEGER,
		BIGINT,
		REAL,
		DOUBLE,
		DECIMAL,
		NUMERIC,
		CHAR,
		BINARY,
		VARCHAR,
		VARBINARY,
		LONGVARCHAR,
		LONGVARBINARY,
		TIMESTAMP,
		DATE,
		TIME,
		YEAR,
		GEOMETRY,
		ENUM,
		SET,
		SqlNULL
	};*/

#endif
