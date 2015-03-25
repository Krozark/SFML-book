#ifndef UTILS_JSON_DRIVER_HPP
#define UTILS_JSON_DRIVER_HPP

#include <iostream>

#include <utils/json/Scanner.hpp>
#include <utils/json/Value.hpp>

namespace utils
{
    /**
     * \brief namspace for json
     */
    namespace json {
        /**
         * A class that have to be use to parse json input
         */
        class Driver
        {
            public:
                /**
                 * \brief Construct a Driver from a stream
                 * \param in input stream
                 */
                Driver(std::istream& in);

                Driver(const Driver&) = delete;
                Driver& operator=(const Driver&) = delete;

                /**
                 * \brief Destructor
                 */
                ~Driver();

                /**
                 * \brief Parse all the input (until \0)
                 */
                Value* parse();

                /**
                 * \return true if the stream is a valid format, else, false.
                 */
                inline bool isValid()const{return validity;}

                /**
                 * \brief Parse a input
                 * \param in The input stream to parse
                 */
                static Value* parse(std::istream& in);

                /**
                 * \brief Parse a input
                 * \param in The input stream to parse
                 */
                static Value* parse(const std::string& in);

                /**
                 * \brief Parse a file and return a Analyse
                 * \param filename the file name
                 * \return A Analyse tha contain all the datas parsed
                 */
                static Value* parse_file(const std::string& filename);


                 
            private:
                friend class Parser;
                    
                Scanner scanner; ///< The lexer
                Parser parser; ///< The parser

                bool validity;//< is valid
                utils::json::Value* value;///< the root node

        };
    }
}
#endif
