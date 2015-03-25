#ifndef UTILS_LOGS_LOG_HPP
#define UTILS_LOGS_LOG_HPP

#include <ostream>

namespace utils
{
/**
 * \brief regroup function for log in a console
 * This functions are output-only I/O manipulator, it may be called with an expression such as out<<bold<<"text"<<reset;
 */
namespace log
{
    
    extern bool show_time;
    /**
     * \brief print a message
     */
    template <typename T,typename ... Args>
    void todo(const T& type,const Args& ... args);

    /**
     * \brief print a message
     */
    template <typename T,typename ... Args>
    void info(const T& type,const Args& ... args);

    /**
     * \brief print a message
     */
    template <typename T,typename ... Args>
    void ok(const T& type,const Args& ... args);

    /**
     * \brief print a message
     */
    template <typename T,typename ... Args>
    void warning(const T& type,const Args& ... args);


    /**
     * \brief print a message
     */
    template <typename T,typename ... Args>
    void error(const T& type,const Args& ... args);

    /**
     * \brief print a message
     */
    template <typename T,typename ... Args>
    void critical(const T& type,const Args& ... args);

    /**
     * \brief print a message
     * if the code value is not 0, exit with that code
     */
    template <typename T,typename ... Args>
    void critical(int code,const T& type,const Args& ... args);

    enum LOG_LVL{
        TODO = 1,
        INFO,
        OK,
        WARN,
        ERR,
        CRIT
    };

    template <typename ... Args>
    void log(LOG_LVL lvl,Args&& ... args);

    /**
     * \brief add the time as : [day-mounth-year hour-min-sec]
     */
    std::ostream& time(std::ostream& output);

    /**
     * \brief change the text format
     */
    namespace format
    {
        std::ostream& bold(std::ostream& output);

        std::ostream& dim(std::ostream& output);

        std::ostream& underline(std::ostream& output);

        std::ostream& blink(std::ostream& output);

        std::ostream& reverse(std::ostream& output);

        std::ostream& hidden(std::ostream& output);

        std::ostream& strikeout(std::ostream& output);



        std::ostream& reset_bold(std::ostream& output);

        std::ostream& reset_dim(std::ostream& output);

        std::ostream& reset_underline(std::ostream& output);

        std::ostream& reset_blink(std::ostream& output);

        std::ostream& reset_reverse(std::ostream& output);

        std::ostream& reset_hidden(std::ostream& output);

        std::ostream& reset_strikeout(std::ostream& output);

        /**
         * \brief reset the format
         * \return output
         */
        std::ostream& reset(std::ostream& output);
    }

    /**
     * \brief change the text color
     */ 
    namespace colors
    {
        std::ostream& black(std::ostream& output);

        std::ostream& red(std::ostream& output);

        std::ostream& green(std::ostream& output);

        std::ostream& yellow(std::ostream& output);

        std::ostream& blue(std::ostream& output);

        std::ostream& magenta(std::ostream& output);

        std::ostream& cyan(std::ostream& output);

        std::ostream& light_gray(std::ostream& output);

        std::ostream& dark_gray(std::ostream& output);

        std::ostream& light_red(std::ostream& output);

        std::ostream& light_green(std::ostream& output);

        std::ostream& light_yellow(std::ostream& output);

        std::ostream& light_blue(std::ostream& output);

        std::ostream& light_magenta(std::ostream& output);

        std::ostream& light_cyan(std::ostream& output);

        std::ostream& white(std::ostream& output);

        std::ostream& reset(std::ostream& output);

    }

    /**
     * \brief change the background color
     */ 
    namespace bg
    {
        std::ostream& black(std::ostream& output);

        std::ostream& red(std::ostream& output);

        std::ostream& green(std::ostream& output);

        std::ostream& yellow(std::ostream& output);

        std::ostream& blue(std::ostream& output);

        std::ostream& magenta(std::ostream& output);

        std::ostream& cyan(std::ostream& output);

        std::ostream& light_gray(std::ostream& output);

        std::ostream& dark_gray(std::ostream& output);

        std::ostream& light_red(std::ostream& output);

        std::ostream& light_green(std::ostream& output);

        std::ostream& light_yellow(std::ostream& output);

        std::ostream& light_blue(std::ostream& output);

        std::ostream& light_magenta(std::ostream& output);

        std::ostream& light_cyan(std::ostream& output);

        std::ostream& white(std::ostream& output);

        std::ostream& reset(std::ostream& output);

    }

}
}
#include <utils/log.tpl>
#endif
