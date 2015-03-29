#include <ORM/backends/MySql/MySqlQuery.hpp>

#include <cppconn/exception.h>
#include <sstream>
#include <iomanip>

namespace orm
{
    MySqlQuery::MySqlQuery(DB& db,const std::string& query) : Query(db,query), db_res(0), prepared_statement(0), statement(0)
    {
    };

    MySqlQuery::MySqlQuery(DB& db,std::string&& query) : Query(db,query), db_res(0), prepared_statement(0), statement(0)
    {
    };

    MySqlQuery::~MySqlQuery()
    {
        if(prepared and prepared_statement)
            delete prepared_statement;
        if(not prepared and statement)
            delete statement;
        if(db_res)
            delete db_res;
    };


    int MySqlQuery::count()const
    {
        return db_res->rowsCount();
    };

    bool MySqlQuery::get(bool& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = db_res->getBoolean((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySqlQuery::get(int& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = db_res->getInt((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySqlQuery::getPk(int& value, const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            if(db_res->isNull((uint32_t)column))
            {
                value = -1;
                return false;
            }
            value = db_res->getUInt((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            value = -1;
            return false;
        }
        #endif
        return true;
    }

    bool MySqlQuery::get(unsigned int& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = db_res->getUInt((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySqlQuery::get(long long int& value,const int& column)const
    {    
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = db_res->getInt64((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySqlQuery::get(long long unsigned int& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = db_res->getUInt64((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySqlQuery::get(float& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = static_cast<float>(db_res->getDouble((uint32_t)column));
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySqlQuery::get(double& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = db_res->getDouble((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySqlQuery::get(long double& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = db_res->getDouble((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };

    bool MySqlQuery::get(std::string& value,const int& column)const
    {
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            value = db_res->getString((uint32_t)column);
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            return false;
        }
        #endif
        return true;
    };
    
    bool MySqlQuery::get(struct tm& value,const int& column)const
    {
        bool res;
        #if ORM_ALLOW_EXCEPTION
        try{
        #endif
            std::string str;
            str = db_res->getString((uint32_t)column);

            int year,mon,day,hour,min,sec;
            res = ::sscanf(str.c_str(),"%4d-%2d-%2d %2d:%2d:%2d",&year,&mon,&day,&hour,&min,&sec) == 6;
            if (res)
            {
                value.tm_year = year;
                value.tm_mon = mon;
                value.tm_mday = day;
                value.tm_hour = hour;
                value.tm_min = min;
                value.tm_sec = sec;
            }
        #if ORM_ALLOW_EXCEPTION
        }
        catch(sql::InvalidArgumentException& e){
            res = false;
        }
        #endif

        return res;
    }

    bool MySqlQuery::next()
    {
        return db_res->next();
    }

    bool MySqlQuery::set(const bool& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setBoolean(column,value);
        return true;
    };

    bool MySqlQuery::set(const int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setInt(column,value);
        return true;
    };

    bool MySqlQuery::set(const unsigned int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setUInt(column,value);
        return true;
    };

    bool MySqlQuery::set(const long long int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setInt64(column,value);
        return true;
    };

    bool MySqlQuery::set(const long long unsigned int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setUInt64(column,value);
        return true;
    };

    bool MySqlQuery::set(const float& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(column,static_cast<double>(value));
        return true;
    };

    bool MySqlQuery::set(const double& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(column,value);
        return true;
    };

    bool MySqlQuery::set(const long double& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setDouble(column,value);
        return true;
    };

    bool MySqlQuery::set(const std::string& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setString(column,value);
        return true;
    };

    bool MySqlQuery::set(const struct tm& value, const unsigned int& column)
    {
        if(not prepared)
            return false;

        std::stringstream stream;
        stream<<std::setfill('0')
            <<std::setw(4)<<value.tm_year
            <<"-"<<std::setw(2)<<value.tm_mon
            <<"-"<<std::setw(2)<<value.tm_mday
            <<" "
            <<std::setw(2)<<value.tm_hour
            <<":"<<std::setw(2)<<value.tm_min
            <<":"<<std::setw(2)<<value.tm_sec;

        prepared_statement->setString(column,stream.str());
        return true;
    }

    bool MySqlQuery::setNull(const int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        prepared_statement->setNull(column,sql::DataType::INTEGER);
        return true;
    };

    void MySqlQuery::executeQuery()
    {
        if(prepared)
            db_res = prepared_statement->executeQuery();
        else
            db_res = statement->executeQuery(query);
    };

};
