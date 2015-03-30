#include <ORM/backends/MySql/MySqlTableCreator.hpp>

namespace orm
{
    
    const std::string mysql_escape(const std::string& column)
    {
       return std::string("`")+column+std::string("`");
    }
    
    MySqlTableCreator::MySqlTableCreator()
    {
    }

    std::string MySqlTableCreator::autoField(const std::string& colunm_name)const
    {
        std::string res = mysql_escape(colunm_name)+" INTEGER AUTO_INCREMENT NOT NULL PRIMARY KEY";
        return res;

    }

    std::string MySqlTableCreator::booleanField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+" BOOL";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string MySqlTableCreator::charField(const std::string& colunm_name,unsigned int max_length,bool nullable)const
    {
        std::string res = mysql_escape(colunm_name)+" VARCHAR("+std::to_string(max_length)+")";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }
    
    // std::string MySqlTableCreator::commaSeparatedIntegerField(const std::string& colunm_nameunsigned int max_length)const;

    std::string MySqlTableCreator::dateField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+" DATE";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string MySqlTableCreator::dateTimeField(const std::string& colunm_name,bool nullable)const
    {
        std::string res = mysql_escape(colunm_name)+" DATETIME";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string MySqlTableCreator::decimalField(const std::string& colunm_name,unsigned int max_digits,unsigned int decimal_places,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+" NUMERIC("+std::to_string(max_digits)+","+std::to_string(decimal_places)+")";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string MySqlTableCreator::floatField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+" DOUBLE PRECISION";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string MySqlTableCreator::doubleField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+" DOUBLE PRECISION";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string MySqlTableCreator::integerField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+" INTEGER";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string MySqlTableCreator::bigIntegerField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+" BIGINT";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }
    
    std::string MySqlTableCreator::oneToOneField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+" INTEGER";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string MySqlTableCreator::fk(const std::string& colunm_name,const std::string& table,bool nullable)const
    {
        std::string res = mysql_escape(colunm_name)+" INTEGER";
        if(not nullable)
            res+= " NOT NULL";
        res+= " REFERENCES " + mysql_escape(table) + "(`pk`)";
        return res;
    }

    std::string MySqlTableCreator::positiveIntegerField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+" INTEGER UNSIGNED";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string MySqlTableCreator::positiveSmallIntegerField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+" SMALLINT UNSIGNED";
        if(nullable)
            res+= " NOT NULL";
        return res;
    }
    
    std::string MySqlTableCreator::smallIntegerField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+std::string(" SMALLINT");
        if(nullable)
            res+= " NOT NULL";
        return res;
    }

    std::string MySqlTableCreator::textField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+std::string(" LONGTEXT");
        if(nullable)
            res+= " NOT NULL";
        return res;
    }
    
    std::string MySqlTableCreator::timeField(const std::string& colunm_name,bool nullable)const
    {
        std::string res=mysql_escape(colunm_name)+std::string(" TIME");
        if(nullable)
            res+= " NOT NULL";
        return res;
    }
    
}
