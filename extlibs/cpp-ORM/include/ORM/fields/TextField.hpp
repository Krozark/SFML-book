#ifndef ORM_TEXTFIELD_HPP
#define ORM_TEXTFIELD_HPP

#include <ORM/fields/private/Attr.hpp>

namespace orm
{
    class TextField : public Attr<std::string>
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in db
             **/
            TextField(const std::string& value,const std::string& column);
            
            /**
             * \brief Make a Attr
             * default value is empty string.
             * \param column Column in db
             **/
            TextField(const std::string& column);

            TextField(const TextField&) = delete;

            using Attr<std::string>::operator=;

            using Attr<std::string>::operator+;

            using Attr<std::string>::operator==;
            using Attr<std::string>::operator!=;
            using Attr<std::string>::operator>;
            using Attr<std::string>::operator<;
            using Attr<std::string>::operator>=;
            using Attr<std::string>::operator<=;

            using Attr<std::string>::operator+=;
            using Attr<std::string>::operator std::string;

        private:
            /**
             * \brief create the attr column
             */
            virtual std::string create(const DB& db) const override;
    };
}
#endif
