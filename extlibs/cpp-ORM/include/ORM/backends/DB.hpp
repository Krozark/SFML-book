#ifndef ORM_DB_HPP
#define ORM_DB_HPP

#include <ORM/externals.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace orm
{
    class Query;
    class VAttr;

    class TableCreator;

    /**
     * \brief Abstract class to deal with any database 
     **/
    class DB
    {
        public:
            /**
            * \brief Create  a Database connection
            *
            * \param username Username to use
            * \param pass Password of the user
            * \param db Database name to use
            * \param serveur IP adresse of the serveur to connect
            * \param port Port to use for the connection
            **/
            DB(const std::string& username,const std::string& pass,const std::string& db,const std::string& serveur,const std::string& port);


            /***
             * \brief Destructor
             **/
            virtual ~DB();

            DB(const DB&) = delete;
            DB& operator=(const DB&) = delete;


            /**
             * \brief Make an explicit copy of the connection
             */
            virtual DB* clone()const = 0;
                
            /**
            * \brief Create the connection with the database
            *
            * \return false if the connection fail
            **/
            virtual bool connect() = 0;

            /**
            * \brief Close the connection with the database
            *
            * \return false if fail
            **/
            virtual bool disconnect() = 0;

            /**
             * \brief Must be call in a thread
             */
            virtual void threadInit() = 0;

            /**
             * \brief Must be call after a end of thread
             */
            virtual void threadEnd() = 0;

            /**
             * \brief Begin transaction
             */
            virtual void beginTransaction() = 0;

            /**
             * \brief END transaction
             */
            virtual void endTransaction() = 0;

            /**
             * \brief rollback
             */
            virtual void rollback() = 0;


            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* query(const std::string& query) = 0;

            /**
            * \brief Create the appropriate Query to make query on the database. Don't forget to delete it after use.
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* query(std::string&&) = 0;

            /**
            * \brief Create a prepared query to execute
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* prepareQuery(const std::string&) = 0;

            /**
            * \brief Create a prepared query to execute
            *
            * \param query The query to execute
            *
            * \return NULL if faild.
            **/
            virtual Query* prepareQuery(std::string&&) = 0;

            /**
             * \brief create a table
             * \param table the table name
             * \param attrs the attrubuts list
             */
            virtual bool create(const std::string& table,const std::vector<const VAttr*>& attrs) = 0;

            /**
             * \brief drop a table
             */
            virtual bool drop(const std::string& table) = 0;

            /**
             * \brief drop a table
             */
            virtual bool clear(const std::string& table) = 0;

            /**
             * \return the creator object
             * Use it to create column in the database
             */
            virtual const TableCreator& creator() const = 0;

            /**
            * \brief The user defined default db to use
            **/
            static DB& Default;

            /**
             * \brief Compare 2 DB
             **/
            bool operator==(const DB& other) const;


            void setUser(const std::string&);

            void setPassword(const std::string&);

            void setDb(const std::string&);

            void setServer(const std::string&);

            void setPort(unsigned int);
            


        protected:
            friend class Query;
            friend class SqlObjectBase;
            friend class VAttr;

            template<typename T> friend class SqlObject;
            template<typename T> friend class QuerySet;
            template<typename T> friend class Cache;
            template<typename T> friend class FKBase;
            template<typename RELATED,typename T> friend class Filter;
            template<typename T,typename U> friend class ManyToMany;
            template<typename T,typename U> friend class M2MQuerySet;

            /* Info for connection */
            std::string s_username; ///< Username use for the connection
            std::string s_password; ///< Username password use for the connection
            std::string s_db_name; ///< Database  name use for the connection
            std::string s_serveur; ///< Ip of tfe serveur to make the connection
            std::string s_port; ///< Port to use for the connection

            /**
            * \brief Map the operators that can be use
            *
            * Operators : \see op
            **/
            std::unordered_map<std::string,std::string> operators;


            /**
            * \brief Get the pk of the last object created in the database
            *
            * \return The pk
            **/
            virtual int getLastInsertPk() = 0;

            /**
            * \brief Save a object in the database
            *
            * \param table Table of the object
            * \param pk PK of the object to save
            * \param attrs column of the oject to save
            *
            * \return false if fail
            *
            * \see update
            **/
            bool save(const std::string& table,int& pk,const std::vector<VAttr*>& attrs);

            /**
            * \brief Update calum value of a object
            *
            * \param table Table of the object
            * \param pk PK of the object to save
            * \param attrs column of the oject to update
            *
            * \return false if fail
            *
            * \see save
            **/
            bool update(const std::string& table,const int& pk,const std::vector<VAttr*>& attrs);

            /**
            * \brief Delete the object
            *
            * \param table Table of the object
            * \param pk PK of the object
            *
            * \return false if fail
            *
            **/
            bool del(const std::string& table,const int& pk);

            /**
            * \brief Escape the String
            *
            * \param column column name to escape
            *
            * \return The escaped column name
            *
            * \see escapeValue
            **/
            virtual std::string escapeColumn(const std::string& column) const;

            /**
            * \brief format the operation for the database
            *
            * \param ope Operation ("gt","lt","exact" ...)
            * \param value  the value to format with the operator (add some '%')
            *
            * \return The formated operation
            *
            * \see operators
            **/
            template<typename T>
            T formatValue(const std::string& ope,T value) const;

            /**
            * \brief format the operation for the database
            *
            * \param ope Operation ("gt","lt","exact" ...)
            *
            * \return The formated operation by adding (?) at the right place
            *
            * \see operators
            **/
            std::string formatPreparedValue(const std::string& ope) const;

            /**
             * \return Return the initial column number for extract values (0 or 1)
             */
            int virtual getInitialGetcolumnNumber() const = 0;

            /**
             * \brief Because limit syntaxe is not the same in all DBMS we need to define it for each one
             *
             * Note : limit(<skip>,<count>) is translante to : "LIMIT [<skip>,]<count>" or "LIMIT <count> [offset <skip>]" for Mysql, Sqlite, Postresql 
             *
             * \param skip Number of object to skip
             * \param count Maximum number of object to return
             *
             * \return *this
             **/
            virtual std::string limit(const int& skip,const int& count) const = 0;

            /**
             * \brief Merge column name to build the alias
             *
             * \param prefix The prefix column alias
             * \param column  The column alias to merge
             * \param args Some optional column alias
             *
             * \return the complet alias
             **/
            template<typename ... Args>
            static std::string makecolumname(DB& db,const std::string& prefix,const std::string& column,Args&& ... args);

            /**
             * \brief Do nothing
             *
             * \param column  The column alias to merge
             *
             * \return column
             **/
            static std::string makecolumname(DB& db,const std::string& prefix,const std::string& column);


    };
};
#include <ORM/backends/DB.tpl>
#endif
