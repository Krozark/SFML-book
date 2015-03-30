#ifndef ORM_CHARFIELD_HPP
#define ORM_CHARFIELD_HPP

#include <ORM/fields/private/Attr.hpp>
#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    template<size_t max_length>
    class CharField : public Attr<std::string>
    {
        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in db
             **/
            CharField(const std::string& value,const std::string& column);

            /**
             * \brief Make a Attr
             * default value is empty string
             * \param column Column in db
             **/
            CharField(const std::string& column);

            CharField(const CharField&) = delete;
            CharField& operator=(const CharField&) = delete;
            
            using Attr<std::string>::operator std::string;

            using Attr<std::string>::operator=;

            using Attr<std::string>::operator+;

            using Attr<std::string>::operator==;
            using Attr<std::string>::operator!=;
            using Attr<std::string>::operator>;
            using Attr<std::string>::operator<;
            using Attr<std::string>::operator>=;
            using Attr<std::string>::operator<=;

            using Attr<std::string>::operator+=;

        private:
            /**
             * \brief create the attr column
             */
            virtual std::string create(const DB& db) const override;
    };
}

#include <ORM/fields/CharField.tpl>
#endif
