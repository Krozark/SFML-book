#include <ORM/backends/Sqlite3/Sqlite3TableCreator.hpp>

namespace orm
{
    const std::string sqlite3_escape(const std::string& column)
    {
       return std::string("\"")+column+std::string("\"");
    }
    
    Sqlite3TableCreator::Sqlite3TableCreator()
    {
    }

    std::string Sqlite3TableCreator::autoField(const std::string& colunm_name)const
    {
        std::string res = sqlite3_escape(colunm_name)+" INTEGER NOT NULL PRIMARY KEY";
        return res;

    }

    std::string Sqlite3TableCreator::booleanField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+" BOOL";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::charField(const std::string& colunm_name,unsigned int max_length,bool nullable)const
    {
        std::string res = sqlite3_escape(colunm_name)+" VARCHAR("+std::to_string(max_length)+")";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    // std::string Sqlite3TableCreator::commaSeparatedIntegerField(const std::string& colunm_nameunsigned int max_length)const;

    std::string Sqlite3TableCreator::dateField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+" DATE";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::dateTimeField(const std::string& colunm_name,bool nullable)const
    {
        std::string res = sqlite3_escape(colunm_name)+" DATETIME";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::decimalField(const std::string& colunm_name,unsigned int max_digits,unsigned int decimal_places,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+" DECIMAL";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::floatField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+" FLOAT";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::doubleField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+" DOUBLE";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::integerField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+" INTEGER";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::bigIntegerField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+" BIGINT";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::oneToOneField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+" INTEGER";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::fk(const std::string& colunm_name,const std::string& table,bool nullable)const
    {
        std::string res = sqlite3_escape(colunm_name)+" INTEGER";
        if(not nullable)
            res+= " NOT NULL";
        res+= " REFERENCES " + sqlite3_escape(table) + "(\"fk\")";
        return res;
    }

    std::string Sqlite3TableCreator::positiveIntegerField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+" INTEGER UNSIGNED";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::positiveSmallIntegerField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+" SMALLINT UNSIGNED";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::smallIntegerField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+std::string(" SMALLINT");
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::textField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+std::string(" TEXT");
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string Sqlite3TableCreator::timeField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=sqlite3_escape(colunm_name)+std::string(" TIME");
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    // std::string Sqlite3TableCreator::binaryField(const std::string& colunm_name,bool nullable)const;
}
