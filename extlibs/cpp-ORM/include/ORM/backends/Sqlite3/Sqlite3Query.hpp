#ifndef ORM_SQLITEQ3UERY_HPP
#define ORM_SQLITE3QUERY_HPP

#include <ORM/backends/Query.hpp>

#include <ORM/backends/Sqlite3/sqlite/sqlite3.h>

namespace orm
{
    class Sqlite3DB;

    /**
     * \brief Abstract class to manage query with sqlite3 only
     **/
    class Sqlite3Query : public Query
    {
        protected:
            
            /**
             * \brief Create a query
             *
             * \param db database where the query will be execute
             * \param query Query string to execute
             **/
            Sqlite3Query(DB& db,const std::string& query);

            /**
             * \brief Create a query
             *
             * \param db database where the query will be execute
             * \param query Query string to execute
             **/
            Sqlite3Query(DB& db,std::string&& query);

            Sqlite3Query(const Sqlite3Query&) = delete;
            Sqlite3Query& operator=(const Sqlite3Query&) = delete;
            
            /**
             * \brief Destructor
             **/
            ~Sqlite3Query();

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
            virtual bool set(const struct tm& value, const unsigned int& column);
            
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
            friend class Sqlite3DB;

            sqlite3_stmt *statement; ///< Hold the  statement
    };
};

/**
 * sqlite 3 data types
SQLITE_INTEGER  1
SQLITE_FLOAT    2
SQLITE_BLOB     4
SQLITE_NULL     5
SQLITE_TEXT     3

const void *sqlite3_column_blob(sqlite3_stmt*, int iCol);
int sqlite3_column_bytes(sqlite3_stmt*, int iCol); //  returns the number of bytes in that BLOB or string.
int sqlite3_column_bytes16(sqlite3_stmt*, int iCol);
double sqlite3_column_double(sqlite3_stmt*, int iCol);
int sqlite3_column_int(sqlite3_stmt*, int iCol);
sqlite3_int64 sqlite3_column_int64(sqlite3_stmt*, int iCol);
const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol);
const void *sqlite3_column_text16(sqlite3_stmt*, int iCol);
int sqlite3_column_type(sqlite3_stmt*, int iCol); // returned value is one of [SQLITE_INTEGER],
** [SQLITE_FLOAT], [SQLITE_TEXT], [SQLITE_BLOB], or [SQLITE_NULL].  

//1 statement
//2 index : 1-> x
//3 value
//4 length in byte of value
//5 SQLITE_STATIC|SQLITE_TRANSIENT. the special value [SQLITE_STATIC], then Sqlite assumes that the
** information is in static, unmanaged space and does not need to be freed.
** ^If the fifth argument has the value [SQLITE_TRANSIENT], then
** Sqlite makes its own private copy of the data immediately, before
** the sqlite3_bind_*() routine returns.

** ^The sqlite3_bind_zeroblob() routine binds a BLOB of length N that
** is filled with zeroes.  ^A zeroblob uses a fixed amount of memory
** (just an integer to hold its size) while it is being processed.
** Zeroblobs are intended to serve as placeholders for BLOBs whose
** content is later written using
** [sqlite3_blob_open | incremental BLOB I/O] routines.
** ^A negative value for the zeroblob results in a zero-length BLOB.

int sqlite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));
int sqlite3_bind_text16(sqlite3_stmt*, int, const void*, int, void(*)(void*));
int sqlite3_bind_value(sqlite3_stmt*, int, const sqlite3_value*);
int sqlite3_bind_zeroblob(sqlite3_stmt*, int, int n);



*/

#endif
