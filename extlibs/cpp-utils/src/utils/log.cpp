#include <utils/log.hpp>

#include <ctime>
#include <iostream>

namespace utils
{
namespace log
{
    bool show_time = true;

    void __out_helper(std::ostream& out)
    {
    }

    std::ostream& time(std::ostream& output)
    {
        time_t temps;
        struct tm* datetime;
        char  format[32];
        ::time(&temps);
        datetime = localtime(&temps);
        strftime(format, 32, "[%d-%m-%Y %H:%M:%S]", datetime);
        output<<format;
        return output;
    }

    namespace format
    {
        std::ostream& bold(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[1m";
            #endif
            return output;
        }

        std::ostream& dim(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[2m";
            #endif
            return output;
        }

        std::ostream& underline(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[4m";
            #endif
            return output;
        }

        std::ostream& blink(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[5m";
            #endif
            return output;
        }

        std::ostream& reverse(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[7m";
            #endif
            return output;
        }

        std::ostream& hidden(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[8m";
            #endif
            return output;
        }

        std::ostream& strikeout(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[9m";
            #endif
            return output;
        }

        std::ostream& reset_bold(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[21m";
            #endif
            return output;
        }

        std::ostream& reset_dim(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[22m";
            #endif
            return output;
        }

        std::ostream& reset_underline(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[24m";
            #endif
            return output;
        }

        std::ostream& reset_blink(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[25m";
            #endif
            return output;
        }

        std::ostream& reset_reverse(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[27m";
            #endif
            return output;
        }

        std::ostream& reset_hidden(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[28m";
            #endif
            return output;
        }

        std::ostream& reset_strikeout(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[29m";
            #endif
            return output;
        }

        std::ostream& reset(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[0m";
            #endif
            return output;
        }
    }

    namespace colors
    {
        std::ostream& black(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[30m";
            #endif
            return output;
        }

        std::ostream& red(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[31m";
            #endif
            return output;
        }

        std::ostream& green(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[32m";
            #endif
            return output;
        }

        std::ostream& yellow(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[33m";
            #endif
            return output;
        }

        std::ostream& blue(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[34m";
            #endif
            return output;
        }

        std::ostream& magenta(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[35m";
            #endif
            return output;
        }

        std::ostream& cyan(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[36m";
            #endif
            return output;
        }

        std::ostream& light_gray(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[37m";
            #endif
            return output;
        }


        std::ostream& dark_gray(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[90m";
            #endif
            return output;
        }

        std::ostream& light_red(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[91m";
            #endif
            return output;
        }

        std::ostream& light_green(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[92m";
            #endif
            return output;
        }

        std::ostream& light_yellow(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[93m";
            #endif
            return output;
        }

        std::ostream& light_blue(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[94m";
            #endif
            return output;
        }

        std::ostream& light_magenta(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[95m";
            #endif
            return output;
        }

        std::ostream& light_cyan(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[96m";
            #endif
            return output;
        }

        std::ostream& white(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[97m";
            #endif
            return output;
        }

        std::ostream& reset(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[39m";
            #endif
            return output;
        }
    }

    namespace bg
    {
        std::ostream& black(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[40m";
            #endif
            return output;
        }

        std::ostream& red(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[41m";
            #endif
            return output;
        }

        std::ostream& green(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[42m";
            #endif
            return output;
        }

        std::ostream& yellow(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[43m";
            #endif
            return output;
        }

        std::ostream& blue(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[44m";
            #endif
            return output;
        }

        std::ostream& magenta(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[45m";
            #endif
            return output;
        }

        std::ostream& cyan(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[46m";
            #endif
            return output;
        }

        std::ostream& light_gray(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[47m";
            #endif
            return output;
        }


        std::ostream& dark_gray(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[100m";
            #endif
            return output;
        }

        std::ostream& light_red(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[101m";
            #endif
            return output;
        }

        std::ostream& light_green(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[102m";
            #endif
            return output;
        }

        std::ostream& light_yellow(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[103m";
            #endif
            return output;
        }

        std::ostream& light_blue(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[104m";
            #endif
            return output;
        }

        std::ostream& light_magenta(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[105m";
            #endif
            return output;
        }

        std::ostream& light_cyan(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[106m";
            #endif
            return output;
        }

        std::ostream& white(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[47m";
            #endif
            return output;
        }

        std::ostream& reset(std::ostream& output)
        {
            #if __unix || __unix__
            output<<"\e[49m";
            #endif
            return output;
        }
    }

}
}
