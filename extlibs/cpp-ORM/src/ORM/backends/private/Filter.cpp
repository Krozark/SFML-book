#include <ORM/backends/private/Filter.hpp>

namespace orm
{
    //special date type
    template<>
    struct tm __filter_value_helper<struct tm>(const struct tm& value)
    {
        tm tmp;
        ::memcpy(&tmp,&value,sizeof(struct tm));
        ::mktime(&tmp);
        tmp.tm_year +=1900;
        tmp.tm_mon +=1;
        tmp.tm_isdst = -1;
        return tmp;
    }

    //special date type
    template<>
    struct tm __filter_clone_helper<struct tm>(const struct tm& value)
    {
        tm tmp;
        ::memcpy(&tmp,&value,sizeof(struct tm));
        tmp.tm_year -=1900;
        tmp.tm_mon -=1;
        tmp.tm_isdst = -1;
        return tmp;
    }
}
