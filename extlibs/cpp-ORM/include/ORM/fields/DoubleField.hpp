#ifndef ORM_doubleEGERFIELD_HPP
#define ORM_doubleEGERFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

namespace orm
{
    class DoubleField : public Attr<double>
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in db
             **/
            DoubleField(const double& value,const std::string& column);
            
            /**
             * \brief Make a Attr
             * default value is 0.
             * \param column Column in db
             **/
            DoubleField(const std::string& column);

            DoubleField(const DoubleField&) = delete;
            DoubleField& operator=(const DoubleField&) = delete;

            using Attr<double>::operator=;

            using Attr<double>::operator+;
            using Attr<double>::operator-;
            using Attr<double>::operator*;
            using Attr<double>::operator/;
            using Attr<double>::operator%;

            using Attr<double>::operator==;
            using Attr<double>::operator!=;
            using Attr<double>::operator>;
            using Attr<double>::operator<;
            using Attr<double>::operator>=;
            using Attr<double>::operator<=;

            using Attr<double>::operator!;

            using Attr<double>::operator+=;
            using Attr<double>::operator-=;
            using Attr<double>::operator*=;
            using Attr<double>::operator/=;
            using Attr<double>::operator%=;
            using Attr<double>::operator double;

        protected:
            /**
             * \brief create the attr column
             */
            virtual std::string create(const DB& db) const;
    };
}
#endif
