#include <ORM/backends/Sqlite3/Sqlite3Query.hpp>
#include <ORM/backends/Sqlite3/Sqlite3DB.hpp>

#include <sstream>
#include <iomanip>


namespace orm
{
    Sqlite3Query::Sqlite3Query(DB& db,const std::string& query) : Query(db,query), statement(0)
    {
        int result = sqlite3_prepare_v2(static_cast<Sqlite3DB&>(db).dbConn,query.c_str(),query.size()+1, &statement, NULL);

        #if ORM_VERBOSITY & ORM_ERROR
        if (result != SQLITE_OK)
        {
            ORM_PRINT_ERROR("Sqlite3Query::Sqlite3Query(db,string&) Failed to make the statment");
            //\todo: "<<sqlite3_errstr(result));
        }
        #endif
    };

    Sqlite3Query::Sqlite3Query(DB& db,std::string&& query) : Query(db,query), statement(0)
    {
        int result = sqlite3_prepare_v2(static_cast<Sqlite3DB&>(db).dbConn,query.c_str(),query.size()+1, &statement, NULL);

        #if ORM_VERBOSITY & ORM_ERROR
        if (result != SQLITE_OK)
        {
            ORM_PRINT_ERROR("Sqlite3Query::Sqlite3Query(db,string&&) Failed to make the statment")
            /// \todo <<sqlite3_errstr(result)<<std::endl;
        }
        #endif
    };

    Sqlite3Query::~Sqlite3Query()
    {
        if(statement)
        {
            int result = sqlite3_finalize(statement);

            #if ORM_VERBOSITY & ORM_ERROR
            if(result != SQLITE_OK)
            {
                ORM_PRINT_ERROR("Sqlite3Query::~Sqlite3Query() Failed to close the statement")
                /// \todo <<sqlite3_errstr(result)<<std::endl;
            }
            #endif
        }
    };


    int Sqlite3Query::count()const
    {
        return sqlite3_data_count(statement);
    };

    bool Sqlite3Query::get(bool& value,const int& column)const
    {
        value = (bool)sqlite3_column_int(statement,column);
        return true;
    };

    bool Sqlite3Query::get(int& value,const int& column)const
    {
        value = sqlite3_column_int(statement,column);
        return true;
    };

    bool Sqlite3Query::getPk(int& value, const int& column)const
    {
        if(sqlite3_column_type(statement,column) == SQLITE_NULL)
        {
            value = -1;
            return false;
        }
        value = sqlite3_column_int(statement,column);
        return true;
    }

    bool Sqlite3Query::get(unsigned int& value,const int& column)const
    {
        value = (unsigned int)sqlite3_column_int(statement,column);
        return true;
    };

    bool Sqlite3Query::get(long long int& value,const int& column)const
    {    
        value = (long long int)sqlite3_column_int64(statement,column);
        return true;
    };

    bool Sqlite3Query::get(long long unsigned int& value,const int& column)const
    {
        value = (unsigned long long int)sqlite3_column_int64(statement,column);

        return true;
    };

    bool Sqlite3Query::get(float& value,const int& column)const
    {
        value = (float)sqlite3_column_double(statement,column);
        return true;
    };

    bool Sqlite3Query::get(double& value,const int& column)const
    {
        value = (double)sqlite3_column_double(statement,column);
        return true;
    };

    bool Sqlite3Query::get(long double& value,const int& column)const
    {
        value = (long double)sqlite3_column_double(statement,column);
        return true;
    };

    bool Sqlite3Query::get(std::string& value,const int& column)const
    {
        const unsigned char* res = sqlite3_column_text(statement,column);

        if (res)
            value = (const char*)res;
        else
            value = "";

        return true;
    };

    bool Sqlite3Query::get(struct tm& value,const int& column)const
    {
        bool res = false;
        const unsigned char* str = sqlite3_column_text(statement,column);
        if (str)
        {
            int year,mon,day,hour,min,sec;
            res = ::sscanf((const char*)str,"%4d-%2d-%2d %2d:%2d:%2d",&year,&mon,&day,&hour,&min,&sec) == 6;
            if (res)
            {
                value.tm_year = year;
                value.tm_mon = mon;
                value.tm_mday = day;
                value.tm_hour = hour;
                value.tm_min = min;
                value.tm_sec = sec;
            }
        }

        return res;
    }

    bool Sqlite3Query::next()
    {
        int result = sqlite3_step(statement);
        if(result == SQLITE_ROW)
            return true;
        else if(result == SQLITE_DONE)
            return false;

        ORM_PRINT_ERROR("Sqlite3Query::next() imposible to get next row, error:"<<result)
        ///\todo sqlite3_errstr(result)<<std::endl;

        return false;

    }

    bool Sqlite3Query::set(const bool& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_int(statement,(int)column,(int)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_int(statement,(int)column,(int)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const unsigned int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_int(statement,(int)column,(int)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const long long int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_int64(statement,(int)column,(sqlite3_int64)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const long long unsigned int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_int64(statement,(int)column,(sqlite3_int64)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const float& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_double(statement,(int)column,(double)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const double& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_double(statement,(int)column,(double)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const long double& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_double(statement,(int)column,(double)value)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const std::string& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_text(statement,(int)column,value.c_str(),-1,SQLITE_TRANSIENT)== SQLITE_OK);
    };

    bool Sqlite3Query::set(const struct tm& value, const unsigned int& column)
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
        return (sqlite3_bind_text(statement,(int)column,stream.str().c_str(),-1,SQLITE_TRANSIENT)== SQLITE_OK);
        
    }

    bool Sqlite3Query::setNull(const int& value,const unsigned int& column)
    {
        if(not prepared)
            return false;
        return (sqlite3_bind_null(statement,(int)column)== SQLITE_OK);
    };
    

    void Sqlite3Query::executeQuery()
    {
    };
    
};
