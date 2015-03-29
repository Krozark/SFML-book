#ifndef ORM_DATETIMEFIELD_HPP
#define ORM_DATETIMEFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

#include <ctime>

namespace orm
{
    /**
     * \brief a field classe to store datetime types.
     * Internaly use struct tm as localtime (from time.h)
     */
    class DateTimeField : public Attr<struct tm>
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in db
             **/            
            DateTimeField(const struct tm& value,const std::string& column);

            /**
             * \brief Make a Attr
             *  default value is false.
             * \param column Column in db
             * 
             **/
            DateTimeField(const std::string& column);


            int& year();///\return the year (format = xxxx)
            int& month(); ///\return the month (format = 1~12)
            int& day(); ///\return the day (format = 0~31)
            int& hour(); ///\return the hours
            int& minute(); ///\return the minutes
            int& second();///\return the second
            int& yday();///\return the number of days sinc 1st january

            /**
             * \brief normalize the internal struct
             * \return the timestamp
             */
            std::time_t mktime();

            /**
             * \brief print the value
             */
            virtual std::ostream& print_value(std::ostream& output)const;

            using Attr<struct tm>::operator tm;///\brief cast operator

            struct tm& operator=(const struct tm& other);


            static struct tm now();///\return the localtime now

            /**
             * \brief construct a tm struct with spécified value
             * \param hour the hour (can be greater than 24)
             * \param min the minutes (can be greater than 59)
             * \param sec the second (can be greater than 59)
             */
            static struct tm time(int hour,int min,int sec);

            /**
             * \brief construct a tm struct with spécified value
             */
            static struct tm date(int year,int month,int day);

            static struct tm day(int nb);///\retrun a tm struc of values of nb days
            static struct tm month(int nb); ///\return a tm struct of nb months
            static struct tm year(int nb);///\return a tm struct of nb days

            /**
             * \brief normalize the param
             * \param time tm to normalize
             * \return the param
             */
            static struct tm& normalize(struct tm& time);

            /**
             * \brief normalize the param
             * \param time tm to normalize
             * \return the param
             */
            static struct tm normalize(struct tm&& time);

        protected:
            
            virtual struct tm prepare_to_db(const struct tm& value);///< convert t to real time (add +1900 y and +1 month)

            virtual struct tm prepare_from_db(const struct tm& value); ///< convert DB to tm

            virtual std::string create(const DB& db) const; ///< get creator

        private:
    };

    /**
     * \brief Same as DateTimeField, but the value is now on first save
     */
    class AutoDateTimeField : public DateTimeField
    {
        public:
            using DateTimeField::DateTimeField;

            using DateTimeField::operator tm;
            using DateTimeField::operator=;

        protected:
            virtual void before_save();
    };

    /**
     * \brief Same as DateTimeField, but the value is now on each save or update on the
     * Object owner
     */
    class AutoNowDateTimeField : public DateTimeField
    {
        public:
            using DateTimeField::DateTimeField;

            using DateTimeField::operator tm;
            using DateTimeField::operator=;

        protected:
            virtual void before_save();
            virtual void before_update();
    };
}

std::ostream& operator<<(std::ostream& stream,const struct tm& time);///\print a tm as "YYYY-MM-DD HH:MM:SS"

bool operator>(const struct tm& first,const struct tm& second);
bool operator>=(const struct tm& first,const struct tm& second);
bool operator<(const struct tm& first,const struct tm& second);
bool operator<=(const struct tm& first,const struct tm& second);
bool operator==(const struct tm& first,const struct tm& second);

struct tm operator+(const struct tm& first,const struct tm& second);
struct tm operator-(const struct tm& first,const struct tm& second);

#endif
