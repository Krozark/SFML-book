#ifndef UTILS_JSON_SCANNER_HPP
#define UTILS_JSON_SCANNER_HPP

#if ! defined(yyFlexLexerOnce)
#define yyFlexLexer UtilsJsonFlexLexer
#include <utils/json/FlexLexer.hpp>
#undef yyFlexLexer
#endif

// Override the interface for yylex since we namespaced it
#undef YY_DECL
#define YY_DECL int utils::json::Scanner::yylex()

// Include Bison for types / tokens
//#if __WIN32
    //#include <utils/json/Win/Parser.hpp>
//#else
    #include <utils/json/Parser.hpp>
//#endif // __WIN32

namespace utils
{
    namespace json {
        class Parser;
        //typename Parser::semantic_type;

        /**
         * \brief The lexer that tokenize the input
         */
        class Scanner : public UtilsJsonFlexLexer
        {
            public:
                /**
                 * \brief Construct from a input
                 * \param in  imput
                 */
                Scanner(std::istream& in);
                Scanner(const Scanner&) = delete;
                Scanner& operator=(const Scanner&) = delete;
                /**
                 * \breif save the pointer to yylval so we can change it, and invoke scanner
                 * \param lval For Lex/bison
                 * \return 0 if all input is parse
                 */
                int yylex(utils::json::Parser::semantic_type *lval);

            protected:

            private:
                /**
                 * \breif Scanning function created by Flex; make this private to force usage
                 * of the overloaded method so we can get a pointer to Bison's yylval
                 */
                int yylex();
                /* yyval ptr */
                utils::json::Parser::semantic_type *yylval; ///< For Lex/bison
        };
    }
}
#endif
