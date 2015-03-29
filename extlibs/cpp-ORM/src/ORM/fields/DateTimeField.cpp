#include <ORM/fields/DateTimeField.hpp>
#include <ORM/backends/private/TableCreator.hpp>

#include <cstring>
#include <cstdio>
#include <iomanip>

namespace orm
{

    DateTimeField::DateTimeField(const struct tm& value,const std::string& column) : Attr(value,column)
    {
    }

    DateTimeField::DateTimeField(const std::string& column) : Attr(tm{0},column)
    {
    }

    int& DateTimeField::year()
    {
        return getValue().tm_year;
    }

    int& DateTimeField::month()
    {
        return getValue().tm_mon;
    }

    int& DateTimeField::day()
    {
        return getValue().tm_mday;
    }

    int& DateTimeField::hour()
    {
        return getValue().tm_hour;
    }

    int& DateTimeField::minute()
    {
        return getValue().tm_min;
    }

    int& DateTimeField::second()
    {
        return getValue().tm_sec;
    }

    int& DateTimeField::yday()
    {
        return getValue().tm_yday;
    }

    std::time_t DateTimeField::mktime()
    {
        return ::mktime(&getValue());
    }

    std::ostream& DateTimeField::print_value(std::ostream& stream) const
    {
        char prev = stream.fill ('x');
        return(stream<<'"'
        <<std::setfill('0')
        <<std::setw(4)<<(_value.tm_year+(prepared?1900:0))
        <<"-"<<std::setw(2)<<(_value.tm_mon+(prepared?1:0))
        <<"-"<<std::setw(2)<<_value.tm_mday<<" "
        <<std::setw(2)<<_value.tm_hour<<":"<<std::setw(2)<<_value.tm_min<<":"<<std::setw(2)<<_value.tm_sec
        <<std::setw(0)<<std::setfill(prev)
        <<'"');
    };


    struct tm& DateTimeField::operator=(const struct tm& other)
    {
        modify = true;
        prepared = true;
        ::memcpy(&_value,&other,sizeof(struct tm));
        return _value;
    }


    struct tm DateTimeField::now()
    {
        /*struct tm tmp;
        time_t t = ::time(nullptr);
        ::localtime_r(&t,&tmp);*/

        /*tmp.tm_year +=1900;
        tmp.tm_mon +=1;*/

        struct tm * timeinfo;
        time_t rawtime;

        std::time(&rawtime);
        timeinfo = std::localtime(&rawtime);

        timeinfo->tm_isdst = -1;
        return *timeinfo;
    }

    struct tm DateTimeField::time(int hour,int min,int sec)
    {
        struct tm tmp{0};
        tmp.tm_year = 0;
        tmp.tm_mon = 0 /*- 1*/;
        tmp.tm_mday = 0;

        tmp.tm_hour = hour;
        tmp.tm_min = min;
        tmp.tm_sec = sec;
        tmp.tm_isdst = -1;
        return tmp;
    }

    struct tm DateTimeField::date(int year,int month,int day)
    {
        struct tm tmp{0};
        tmp.tm_year = year /*- 1900*/;
        tmp.tm_mon = month /*- 1*/;
        tmp.tm_mday = day;
        tmp.tm_isdst = -1;
        return tmp;
    }

    struct tm DateTimeField::day(int nb)
    {
        struct tm tmp{0};
        tmp.tm_mday = nb;
        tmp.tm_isdst = -1;
        return tmp;
    }

    struct tm DateTimeField::month(int nb)
    {
        struct tm tmp{0};
        tmp.tm_mon = nb;
        tmp.tm_isdst = -1;
        return tmp;
    }

    struct tm DateTimeField::year(int nb)
    {
        struct tm tmp{0};
        tmp.tm_year = nb;
        tmp.tm_isdst = -1;
        return tmp;
    }

    struct tm& DateTimeField::normalize(struct tm& time)
    {
        ::mktime(&time);
        return time;
    }

    struct tm DateTimeField::normalize(struct tm&& time)
    {
        ::mktime(&time);
        return time;
    }

    struct tm DateTimeField::prepare_to_db(const struct tm& value)
    {
        tm tmp;
        ::memcpy(&tmp,&value,sizeof(struct tm));
        ::mktime(&tmp);
        tmp.tm_year +=1900;
        tmp.tm_mon +=1;
        tmp.tm_isdst = -1;
        return tmp;
    }

    struct tm DateTimeField::prepare_from_db(const struct tm& value)
    {
        tm tmp;
        ::memcpy(&tmp,&value,sizeof(struct tm));
        tmp.tm_year -=1900;
        tmp.tm_mon -=1;
        tmp.tm_isdst = -1;
        ::mktime(&tmp);
        return tmp;
    }

    std::string DateTimeField::create(const DB& db) const
    {
        return db.creator().dateTimeField(column,false);
    }

    //AutoDateTimeField
    void AutoDateTimeField::before_save()
    {
        *this=DateTimeField::now();
    }

    //AutoNowDateTimeField
    void AutoNowDateTimeField::before_save()
    {
        *this=DateTimeField::now();
    }

    void AutoNowDateTimeField::before_update()
    {
        *this=DateTimeField::now();
    }
}

std::ostream& operator<<(std::ostream& stream,const struct tm& time)
{
    char prev = stream.fill ('x');
    stream<<std::setfill('0')
        <<std::setw(4)<<time.tm_year<<"-"<<std::setw(2)<<time.tm_mon<<"-"<<std::setw(2)<<time.tm_mday<<" "
        <<std::setw(2)<<time.tm_hour<<":"<<std::setw(2)<<time.tm_min<<":"<<std::setw(2)<<time.tm_sec
        <<std::setw(0)<<std::setfill(prev);
    return stream;
}

bool operator>(const struct tm& first,const struct tm& second)
{
    struct tm _1,
              _2;
    ::memcpy(&_1,&first,sizeof(struct tm));
    ::memcpy(&_2,&second,sizeof(struct tm));

    return mktime(&_1) > ::mktime(&_2);
}

bool operator>=(const struct tm& first,const struct tm& second)
{
    struct tm _1,
              _2;
    ::memcpy(&_1,&first,sizeof(struct tm));
    ::memcpy(&_2,&second,sizeof(struct tm));

    return mktime(&_1) >= ::mktime(&_2);
}

bool operator<(const struct tm& first,const struct tm& second)
{
    struct tm _1,
              _2;
    ::memcpy(&_1,&first,sizeof(struct tm));
    ::memcpy(&_2,&second,sizeof(struct tm));

    return mktime(&_1) < ::mktime(&_2);
}

bool operator<=(const struct tm& first,const struct tm& second)
{
    struct tm _1,
              _2;
    ::memcpy(&_1,&first,sizeof(struct tm));
    ::memcpy(&_2,&second,sizeof(struct tm));

    return mktime(&_1) <= ::mktime(&_2);
}

bool operator==(const struct tm& first,const struct tm& second)
{
    struct tm _1,
              _2;
    ::memcpy(&_1,&first,sizeof(struct tm));
    ::memcpy(&_2,&second,sizeof(struct tm));

    return mktime(&_1) == ::mktime(&_2);
}

struct tm operator+(const struct tm& first,const struct tm& second)
{
    struct tm tmp;
    ::memcpy(&tmp,&first,sizeof(struct tm));
    tmp.tm_sec += second.tm_sec;
    tmp.tm_min += second.tm_min;
    tmp.tm_hour += second.tm_hour;
    tmp.tm_mday += second.tm_mday;
    tmp.tm_mon += second.tm_mon;
    tmp.tm_year += second.tm_year;
    tmp.tm_isdst = -1;
    //::mktime(&tmp);
    return tmp;
}

struct tm operator-(const struct tm& first,const struct tm& second)
{
    struct tm tmp;
    ::memcpy(&tmp,&first,sizeof(struct tm));
    tmp.tm_sec -= second.tm_sec;
    tmp.tm_min -= second.tm_min;
    tmp.tm_hour -= second.tm_hour;
    tmp.tm_mday -= second.tm_mday;
    tmp.tm_mon -= second.tm_mon;
    tmp.tm_year -= second.tm_year;
    tmp.tm_isdst = -1;
    //::mktime(&tmp);
    return tmp;
}

