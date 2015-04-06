#include <stdio.h>

#include <ORM/backends/DB.hpp>
#include <ORM/backends/Query.hpp>
#include <ORM/models/SqlObjectBase.hpp>
#include <ORM/fields/private/VAttr.hpp>

namespace orm
{

    DB::DB(const std::string& username,const std::string& pass,const std::string& db,const std::string& serveur,const std::string& port) : s_username(username),
        s_password(pass),
        s_db_name(db),
        s_serveur(serveur),
        s_port(port)
    {
    };

    DB::~DB()
    {
    }

    bool DB::operator==(const DB& other) const
    {
        return (
                (s_db_name == other.s_db_name)
                and (s_serveur == other.s_serveur)
                and (s_port == other.s_port)
                //and (s_username == other.s_username)
                //and (s_password === other.s_password)
                );
    }
    void DB::setUser(const std::string& user)
    {
        s_username = user;
    }

    void DB::setPassword(const std::string& pass)
    {
        s_password = pass;
    }

    void DB::setDb(const std::string& db)
    {
        s_db_name = db;
    }

    void DB::setServer(const std::string& server)
    {
        s_serveur = server;
    }

    void DB::setPort(unsigned int port)
    {
        s_port = std::to_string(port);
    }

    bool DB::save(const std::string& table,int& pk,const std::vector<VAttr*>& attrs)
    {
        const unsigned int size = attrs.size();
        if(size > 0)
        {
            std::string str_q = "INSERT INTO "+escapeColumn(table)+"("+attrs[0]->column;

            for(unsigned int i=1;i<size;++i)
                str_q+=","+attrs[i]->column;
            str_q+=") ";

            str_q+="VALUES ((?)";
            for(unsigned int i=1;i<size;++i)
                str_q+=",(?)";
            str_q+=");";
            
            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<BLEU<<"[Sql:insert] "<<str_q<<"\nVALUES = (";
            #endif

            Query& q = *prepareQuery(str_q);

            for(unsigned int i=0;i<size;++i)
            {
                //prepare the field
                attrs[i]->before_save();

                #if ORM_DEBUG & ORM_DEBUG_SQL
                std::cerr<<","<<*attrs[i];
                #endif
                attrs[i]->set(q,i+1);
                attrs[i]->modify = false;
                //post save
                attrs[i]->after_save();
            }
            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<")"<<std::endl;
            #endif

            q.execute();
            q.next();
            delete &q;

            pk = getLastInsertPk();
            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<JAUNE<<"new PK: "<<pk<<" in table "<<table<<BLANC<<std::endl;
            #endif

            return true;

        }
        return -1;
    };

    bool DB::update(const std::string& table,const int& pk,const std::vector<VAttr*>& attrs)
    {
        const unsigned int size = attrs.size();
        if(size > 0)
        {
            std::string str_q = "UPDATE "+escapeColumn(table)+" SET ";

            bool first(true);
            for(unsigned int i=0;i<size;++i)
            {
                //prepare the field (can change modify)
                attrs[i]->before_update();

                if(attrs[i]->modify)
                {
                    if(not first)
                        str_q+=", ";
                    first = false;
                    str_q+=attrs[i]->column+"=(?)";

                }
            }

            str_q+=" WHERE "+escapeColumn(table)+"."+escapeColumn("pk")+" = "+std::to_string(pk)+";"; ///< \todo column.id
            

            if(first) //NO MAJ NEDEED
            {
                #if ORM_DEBUG & ORM_DEBUG_SQL
                std::cerr<<BLEU2<<"[Sql:update] "<<str_q<<"\nNo Update needed, exit"<<BLANC<<std::endl;
                #endif

                return false;
            }

            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<BLEU2<<"[Sql:update] "<<str_q<<"\nVALUES = (";
            #endif

            Query& q = *prepareQuery(str_q);
            
            int index=1;
            for(unsigned int i=0;i<size;++i)
            {
                if(attrs[i]->modify)
                {
                    #if ORM_DEBUG & ORM_DEBUG_SQL
                    attrs[i]->print_value(std::cerr)<<",";
                    #endif
                    attrs[i]->set(q,index++);
                    attrs[i]->modify = false;
                    //after update (can change modify)
                    attrs[i]->after_update();
                }
            }

            #if ORM_DEBUG & ORM_DEBUG_SQL
            std::cerr<<")"<<BLANC<<std::endl;
            #endif
            q.execute();
            q.next();
            delete &q;

        }
        return true;
    };

    bool DB::del(const std::string& table,const int& pk)
    {
        std::string str_q = "DELETE FROM "+escapeColumn(table)+" WHERE ("+escapeColumn(table)+"."+escapeColumn("pk")+" = "+std::to_string(pk)+");";

        #if ORM_DEBUG & ORM_DEBUG_SQL
        std::cerr<<COMMENTAIRE<<"[Sql:delete]"<<str_q<<BLANC<<std::endl;
        #endif

        Query* q = prepareQuery(str_q);
        q->execute();
        q->next();
        delete  q;

        return true;
    };

    std::string DB::escapeColumn(const std::string& str) const
    {
        return "'"+str+"'";
    }

    void ReplaceStringInPlace(std::string& subject, const std::string& search,const std::string& replace)
    {
        size_t pos = 0;
        while((pos = subject.find(search, pos)) != std::string::npos)
        {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }

    template<>
    std::string DB::formatValue(const std::string& filter,std::string value) const
    {
        if(filter == "contains")
        {
            value = "%"+value+"%";
        }
        else if(filter == "icontains")
        {
            value = "%"+value+"%";
        }
        else if(filter == "startswith")
        {
            value = value+"%";
        }
        else if(filter == "endswith" )
        {
            value = "%"+value;
        }
        else if(filter == "istartswith")
        {
            value = value+"%";
        }
        else if(filter == "iendswith")
        {
            value = "%"+value;
        }

        return value;
    }

    std::string DB::formatPreparedValue(const std::string& filter) const
    {
        const std::string& op = operators.at(filter);
        char buffer[op.size() + 3];
        sprintf(buffer,op.c_str(),"(?)");

        return std::string(buffer);
    }


    std::string DB::makecolumname(DB& db,const std::string& prefix,const std::string& column)
    {
        return db.escapeColumn(prefix)+"."+db.escapeColumn(column);
    }
};
//orm::DB* orm::DB::Default = 0;

