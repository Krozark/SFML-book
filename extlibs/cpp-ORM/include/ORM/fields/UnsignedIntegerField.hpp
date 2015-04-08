#ifndef ORM_UNSIGNEDINTEGERFIELD_HPP
#define ORM_UNSIGNEDINTEGERFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

namespace orm
{
    class UnsignedIntegerField : public Attr<unsigned int>
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in db
             **/
            UnsignedIntegerField(const int& value,const std::string& column);
            
            /**
             * \brief Make a Attr
             * default value is 0.
             * \param column Column in db
             **/
            UnsignedIntegerField(const std::string& column);

            UnsignedIntegerField(const UnsignedIntegerField&) = delete;

            using Attr<unsigned int>::operator=;

            using Attr<unsigned int>::operator+;
            using Attr<unsigned int>::operator-;
            using Attr<unsigned int>::operator*;
            using Attr<unsigned int>::operator/;
            using Attr<unsigned int>::operator%;

            using Attr<unsigned int>::operator++;
            using Attr<unsigned int>::operator--;

            using Attr<unsigned int>::operator==;
            using Attr<unsigned int>::operator!=;
            using Attr<unsigned int>::operator>;
            using Attr<unsigned int>::operator<;
            using Attr<unsigned int>::operator>=;
            using Attr<unsigned int>::operator<=;

            using Attr<unsigned int>::operator!;

            using Attr<unsigned int>::operator+=;
            using Attr<unsigned int>::operator-=;
            using Attr<unsigned int>::operator*=;
            using Attr<unsigned int>::operator/=;
            using Attr<unsigned int>::operator%=;
            using Attr<unsigned int>::operator unsigned int;

        private:
            /**
             * \brief create the attr column
             */
            virtual std::string create(const DB& db) const override;
    };
}
#endif
