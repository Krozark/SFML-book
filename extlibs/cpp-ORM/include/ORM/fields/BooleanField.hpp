#ifndef ORM_BOOLEANFIELD_HPP
#define ORM_BOOLEANFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

namespace orm
{
    class BooleanField : public Attr<bool>
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in db
             **/
            BooleanField(const bool& value,const std::string& column);

            /**
             * \brief Make a Attr
             *  default value is false.
             * \param column Column in db
             * 
             **/
            BooleanField(const std::string& column);

            BooleanField(const BooleanField&) = delete;
            BooleanField& operator=(const BooleanField&) = delete;

            using Attr<bool>::operator=;

            using Attr<bool>::operator+;
            using Attr<bool>::operator-;
            using Attr<bool>::operator*;
            using Attr<bool>::operator/;

            using Attr<bool>::operator==;
            using Attr<bool>::operator!=;
            using Attr<bool>::operator>;
            using Attr<bool>::operator<;
            using Attr<bool>::operator>=;
            using Attr<bool>::operator<=;

            using Attr<bool>::operator!;

            using Attr<bool>::operator+=;
            using Attr<bool>::operator-=;
            using Attr<bool>::operator bool;

        private:
            /**
             * \brief create the attr column
             */
            virtual std::string create(const DB& db) const override;
    };
}
#endif
