#include <iostream>
#include <cstdlib>
namespace utils
{
namespace log
{
    /////////// HELPERS ////////////////////
    void __out_helper(std::ostream& out);

    template <typename T,typename ... Args>
    void __out_helper(std::ostream& out,const T& p,const Args& ... args)
    {
        out<<" "<<p;
        __out_helper(out,args ...);
    }

    ////////////// TODO //////////////////////
    template <typename T>
    void todo(const T& msg)
    {
        std::clog<<colors::yellow;
        if(show_time)
            std::clog<<time;
        std::clog<<msg
            <<colors::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void todo(const T& type,const Args& ... args)
    {
        std::clog<<colors::yellow;
        if(show_time)
            std::clog<<time;
        std::clog<<"["<<type<<"]";
        __out_helper(std::clog,args ...);
        std::clog<<colors::reset<<std::endl;
    }
    //////////////////// info //////////////////////
    template <typename T>
    void info(const T& msg)
    {
        std::clog<<colors::light_cyan;
        if(show_time)
            std::clog<<time;
        std::clog<<msg
            <<colors::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void info(const T& type,const Args& ... args)
    {
        std::clog<<colors::light_cyan;
        if(show_time)
            std::clog<<time;
        std::clog<<"["<<type<<"]";
        __out_helper(std::clog,args ...);
        std::clog<<colors::reset<<std::endl;
    }

    //////////////////// ok //////////////////////
    template <typename T>
    void ok(const T& msg)
    {
        std::clog<<colors::green;
        if(show_time)
            std::clog<<time;
        std::clog<<msg
            <<colors::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void ok(const T& type,const Args& ... args)
    {
        std::clog<<colors::green;
        if(show_time)
            std::clog<<time;
        std::clog<<"["<<type<<"]";
        __out_helper(std::clog,args ...);
        std::clog<<colors::reset<<std::endl;
    }

    /////////// WARNING //////////////
    template <typename T>
    void warning(const T& msg)
    {
        std::clog<<colors::magenta;
        if(show_time)
            std::clog<<time;
        std::clog<<msg
            <<colors::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void warning(const T& type,const Args& ... args)
    {
        std::clog<<colors::magenta;
        if(show_time)
            std::clog<<time;
        std::clog<<"["<<type<<"]";
        __out_helper(std::clog,args ...);
        std::clog<<colors::reset<<std::endl;
    }
    ////////////// ERROR ///////////////
    template <typename T>
    void error(const T& msg)
    {
        std::clog<<colors::red;
        if(show_time)
            std::clog<<time;
        std::clog<<msg
            <<colors::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void error(const T& type,const Args& ... args)
    {
        std::clog<<colors::red;
        if(show_time)
            std::clog<<time;
        std::clog<<"["<<type<<"]";
        __out_helper(std::clog,args ...);
        std::clog<<colors::reset<<std::endl;
    }
    ///////////////// CRITICAL ///////////////
    template <typename T>
    void critical(const T& msg)
    {
        std::clog<<format::bold<<bg::red;
        if(show_time)
            std::clog<<time;
        std::clog<<msg
            <<format::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void critical(const T& type,const Args& ... args)
    {
        std::clog<<format::bold<<bg::red;
        if(show_time)
            std::clog<<time;
        std::clog<<"["<<type<<"]"<<type;
        __out_helper(std::clog,args ...);
        std::clog<<format::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void critical(int code,const T& type,const Args& ... args)
    {
        if(code != 0)
        {
            critical(type,args...,". Exit with code:",code);
            std::exit(code);
        }
        else
            critical(type,args...);
    }


    template <typename ... Args>
    void log(LOG_LVL lvl,Args&& ... args)
    {
        switch(lvl)
        {
            case TODO:
                todo(args ...);break;
            case INFO:
                info(args...);break;
            case OK:
                ok(args...);break;
            case WARN:
                warning(args ...);break;
            case ERR:
                error(args ...); break;
            case CRIT:
                critical(args ...);break;
            default:
                error("utils::log::log()","Unknow value of lvl. Message show as info:");
                info(args ...);
                break;

        }
    }
}
}
