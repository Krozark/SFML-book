#ifndef ORM_FLOATFIELD_HPP
#define ORM_FLOATFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

namespace orm
{
    class FloatField : public Attr<float>
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in db
             **/
            FloatField(const float& value,const std::string& column);
            
            /**
             * \brief Make a Attr
             * default value is 0.
             * \param column Column in db
             **/
            FloatField(const std::string& column);

            FloatField(const FloatField&) = delete;
            FloatField& operator=(const FloatField&) = delete;

            using Attr<float>::operator=;

            using Attr<float>::operator+;
            using Attr<float>::operator-;
            using Attr<float>::operator*;
            using Attr<float>::operator/;
            using Attr<float>::operator%;

            using Attr<float>::operator==;
            using Attr<float>::operator!=;
            using Attr<float>::operator>;
            using Attr<float>::operator<;
            using Attr<float>::operator>=;
            using Attr<float>::operator<=;

            using Attr<float>::operator!;

            using Attr<float>::operator+=;
            using Attr<float>::operator-=;
            using Attr<float>::operator*=;
            using Attr<float>::operator/=;
            using Attr<float>::operator%=;
            using Attr<float>::operator float;

        private:
            /**
             * \brief create the attr column
             */
            virtual std::string create(const DB& db) const override;
    };
}
#endif
