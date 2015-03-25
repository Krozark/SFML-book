#ifndef UTILS_JSON_ARRAY_HPP
#define UTILS_JSON_ARRAY_HPP

#include <utils/json/Value.hpp>
#include <list>
#include <iostream>

namespace utils
{
    namespace json
    {
        /**
         * \brief class to manage the special Array value
         * Internaly stored as a list. Operator [] is not allowed
         */
        class Array
        {
            public:
                explicit Array();

                Array(const Array&) = delete;
                Array& operator=(const Array&) = delete;

                Array(Array&&) = default;
                Array& operator=(Array&&) = default;
                
                friend std::ostream& operator<<(std::ostream& stream, const Array& self); //< output as json

                std::list<Value>::const_iterator begin() const;

                std::list<Value>::const_iterator end() const;

                std::list<Value>::iterator begin();

                std::list<Value>::iterator end();

                size_t size() const; //< return the size


            private:
                friend class Value;
                friend class Parser;

                void print_ident(std::ostream& out,int i)const;

                std::list<Value> values;

        };
    }
}
#endif
