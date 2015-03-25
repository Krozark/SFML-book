#ifndef UTILS_JSON_OBJECT_HPP
#define UTILS_JSON_OBJECT_HPP

#include <utils/json/Value.hpp>
#include <unordered_map>
#include <iostream>

namespace utils
{
    namespace json
    {
        /**
         * \brief a class to manage JSon objects
         * Stored as std::unordered_map
         */
        class Object
        {
            public:
                explicit Object();

                Object(const Object&) = delete;
                Object& operator=(const Object&) = delete;

                Object(Object&&) = default;
                Object& operator=(Object&&) = default;

                friend std::ostream& operator<<(std::ostream& stream, const Object& self); //< output as json

                /**
                 * \return the Value with key key
                 * Note a new one is create if key does't exist
                 */
                Value& operator[] (const std::string& key);

                /**
                 * \return the Value with key key
                 * Note make a error is key is not valid
                 */
                const Value& operator[] (const std::string& key) const;

                std::unordered_map<std::string, Value>::const_iterator begin() const;

                std::unordered_map<std::string, Value>::const_iterator end() const;

                std::unordered_map<std::string, Value>::iterator begin();

                std::unordered_map<std::string, Value>::iterator end();

                //std::pair<std::unordered_map<std::string, Value>::iterator, bool> insert(const std::pair<std::string, Value>& v);
                
                size_t size() const; //< return the object size


            private:
                friend class Parser;
                friend class Value;

                std::unordered_map<std::string,Value> values;

                static void ident(std::ostream& out,int);

                void print_ident(std::ostream& out,int i)const;

        };
    }
}
#endif
