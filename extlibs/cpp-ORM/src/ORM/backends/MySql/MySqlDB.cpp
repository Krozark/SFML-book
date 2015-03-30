#include  <ORM/backends/MySql/MySqlDB.hpp>
#include  <ORM/backends/MySql/MySqlQuery.hpp>

#include <ORM/fields/private/VAttr.hpp>
#include <ORM/backends/op.hpp>

#include <cppconn/exception.h>

namespace orm
{
    MySqlTableCreator MySqlDB::my_creator;

    MySqlDB::MySqlDB(std::string username,std::string pass,std::string db,std::string serveur,std::string port) :
        DB(username,pass,db,serveur,port),
        driver(0),
        dbConn(0)
    {
        //Operators
        operators[op::exact]= " = %s";
        operators[op::iexact]= " LIKE %s";
        operators[op::contains]= " LIKE BINARY %s";
        operators[op::icontains]= " LIKE %s";
        operators[op::regex]= " REGEXP BINARY %s";
        operators[op::iregex]= " REGEXP %s";
        operators[op::gt]= " > %s";
        operators[op::gte]= " >= %s";
        operators[op::lt]= " < %s";
        operators[op::lte]= " <= %s";
        operators[op::startswith]= " LIKE BINARY %s";
        operators[op::endswith]= " LIKE BINARY %s";
        operators[op::istartswith]= " LIKE %s";
        operators[op::iendswith]= " LIKE %s";

        //ordering
        operators["?"] = " RAND() ";
        operators["+"] = " ASC ";
        operators["-"] = " DESC ";

        //escape_char = "";
    };

    MySqlDB::~MySqlDB()
    {
        if(dbConn)
            delete dbConn;
    };

    DB* MySqlDB::clone()const
    {
        MySqlDB* copy = new MySqlDB(this->s_username,this->s_password,this->s_db_name,this->s_serveur,this->s_port);
        return copy;
    }
    
    bool MySqlDB::connect()
    {
        try{
            driver = get_driver_instance();
        }catch (sql::SQLException& e){
            std::cerr << "Could not get a database driver. Error message: " << e.what() <<std::endl;
            return false;
        }

        try{
            dbConn = driver->connect(s_serveur+":"+s_port,s_username,s_password);
        }
        catch (sql::SQLException& e){
            std::cerr<< "Could not connect to database. Error message: " << e.what() << std::endl;
            return false;
        }

        sql::Statement* statement = dbConn->createStatement();
        statement->execute("USE "+escapeColumn(s_db_name));

        std::cerr<<"MySqlDB::Connect to "<<s_serveur<<" using database: "<<s_db_name<<std::endl;

        delete statement;

        return true;
    };

    bool MySqlDB::disconnect()
    {
        return true;
    };

    void MySqlDB::threadInit()
    {
        driver->threadInit();
    }

    void MySqlDB::threadEnd()
    {
        driver->threadEnd();
    }

    Query* MySqlDB::query(const std::string& str)
    {
        auto q = new MySqlQuery(*this,str);
        q->statement = dbConn->createStatement();
        q->prepared = false;
        return q;
    };

    Query* MySqlDB::query(std::string&& str)
    {
        auto q = new MySqlQuery(*this,str);
        q->statement = dbConn->createStatement();
        q->prepared = false;
        return q;
    };


    Query* MySqlDB::prepareQuery(const std::string& str)
    {
        auto q = new MySqlQuery(*this,str);
        q->prepared_statement = dbConn->prepareStatement(str);
        q->prepared = true;
        return q;
    };

    Query* MySqlDB::prepareQuery(std::string&& str)
    {
        auto q = new MySqlQuery(*this,str);
        q->prepared_statement = dbConn->prepareStatement(str);
        q->prepared = true;
        return q;
    }

    bool MySqlDB::create(const std::string& table,const std::vector<const VAttr*>& attrs)
    {
        std::string sql = "CREATE TABLE "+escapeColumn(table)+"(\n";
        unsigned int size = attrs.size();
        sql+= creator().autoField("pk");

        const DB& db=*this;
        for(unsigned int i=0;i<size;++i)
        {
            sql+=",\n"+attrs[i]->create(db);
        }
        sql+="\n);";

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    }

    bool MySqlDB::drop(const std::string& table)
    {
        std::string sql = "DROP TABLE "+escapeColumn(table)+";";

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    }

    bool MySqlDB::clear(const std::string& table)
    {

        std::string sql = "TRUNCATE "+escapeColumn(table)+";";

        Query* q = this->query(sql);
        q->execute();
        q->next();
        delete q;

        return true;
    }

    /************** PROTECTED **********************/
    
    void MySqlDB::beginTransaction()
    {
        sql::Statement* statement = dbConn->createStatement();
        statement->execute("START TRANSACTION;");
        delete statement;
    };

    void MySqlDB::endTransaction()
    {
        sql::Statement* statement = dbConn->createStatement();
        statement->execute("COMMIT;");
        delete statement;
    };

    void MySqlDB::rollback()
    {
        sql::Statement* statement = dbConn->createStatement();
        statement->execute("ROLLBACK;");
        delete statement;
    };

    int MySqlDB::getLastInsertPk()
    {
        Query& q = *query("SELECT LAST_INSERT_ID();");

        q.execute();
        q.next();

        int pk = -1;
        q.get(pk,getInitialGetcolumnNumber());

        delete &q;

        return pk;
    }

    std::string MySqlDB::escapeColumn(const std::string& str) const
    {
        return "`"+str+"`";
    }

    int MySqlDB::getInitialGetcolumnNumber() const
    {
        return 1;
    }

    std::string MySqlDB::limit(const int& skip,const int& count)const
    {
        std::string query;
        if(skip > 0 and count > 0)
            query+=" LIMIT "+std::to_string(skip)+" , "+std::to_string(count);
        else if (count > 0)
            query+=" LIMIT "+std::to_string(count);
        else
            std::cerr<<ROUGE<<"[ERROR] Limit : count can't be <= 0"<<std::endl;
        return query;
    };
    
    const TableCreator& MySqlDB::creator() const
    {
        return my_creator;
    }
    
};
