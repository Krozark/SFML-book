 /* use newer C++ skeleton file */
%skeleton "lalr1.cc"
/* Require bison version or later */
%require "3.0"
/* verbose error messages */
/*%error-verbose*/
/* namespace to enclose parser in */
%define api.namespace {utils::json}
/* set the parser's class identifier */
%define parser_class_name {Parser}

%lex-param { utils::json::Scanner& scanner }
%parse-param { utils::json::Scanner& scanner }

/*%lex-param { utils::json::Driver& driver }*/
%parse-param { utils::json::Driver& driver }

%code requires {

    #include <utility>
    #include <utils/json/Value.hpp>
    #include <utils/json/Array.hpp>
    #include <utils/json/Object.hpp>

    extern int json_line_no; 

    namespace utils {
        namespace json {
            class Scanner;
            class Driver;
        }
    }


}

%code{
    #include <utils/json/Driver.hpp>
    #include <string>
	/*Prototype for the yylex function*/
	static int yylex(utils::json::Parser::semantic_type* yylval, utils::json::Scanner& scanner);

    #define DEL(x) delete x; x=nullptr;
}



%union
{
    // "Pure" types
    long long int   v_int;
    long double     v_float;
    bool            v_bool;
    std::string*    v_string;
    // Pointers to more complex classes
    utils::json::Object* v_object;
    utils::json::Array* v_array;
    utils::json::Value* v_value;
} 

    
/** Declare tokens */
%token      T_SQUARE_BRACKET_L        "square bracket left"
%token      T_SQUARE_BRACKET_R        "square bracket right"
%token      T_CURLY_BRACKET_L         "curry bracket left"
%token      T_CURLY_BRACKET_R         "curry bracket right"
%token      T_COMMA                   "coma"
%token      T_COLON                   "colon"

%token      T_NUMBER_I                "integer"
%token      T_NUMBER_F                "float"
%token      T_BOOLEAN                 "boolean"
%token      T_NULL                    "null"
%token      T_DOUBLE_QUOTED_STRING    "double quoted string"


%start start
/** Define types for union values */
%type<v_int>    T_NUMBER_I
%type<v_float>  T_NUMBER_F
%type<v_bool>   T_BOOLEAN
%type<v_string> T_DOUBLE_QUOTED_STRING str
%type<v_value>  value
%type<v_array>  array list 
%type<v_object> object assignment_list


%%

// Entry point (every JSON file represents a value)
start: value {
     driver.value = $1;
     };

object: T_CURLY_BRACKET_L assignment_list T_CURLY_BRACKET_R {
      $$=$2;
      $2=nullptr;
}
      ;

array : T_SQUARE_BRACKET_L list T_SQUARE_BRACKET_R {
      $$=$2;
      $2=nullptr;
      }
      ;

str : T_DOUBLE_QUOTED_STRING {
    $$=new std::string($1->substr(1,$1->length()-2));
    DEL($1);
    }
    ;

value : str        {
        $$=new utils::json::Value($1);
        $1=nullptr;
      }
      | T_NUMBER_I {
        $$=new utils::json::Value($1);
      }
      | T_NUMBER_F {
        $$=new utils::json::Value($1);
      }
      | object     {
        $$=new utils::json::Value($1);
        $1=nullptr;
      }
      | array      {
        $$=new utils::json::Value($1);
        $1=nullptr;
      }
      | T_BOOLEAN  {
        $$=new utils::json::Value($1);
      }
      | T_NULL     {
        $$=new utils::json::Value();
      }
      ;

list : /* empty */ {
        $$=new utils::json::Array();
     }
     | value {
        $$=new utils::json::Array();
        $$->values.push_back(std::move(*$1));
        DEL($1);
    }/*new*/
    | list T_COMMA value {
        $$=$1;
        $1=nullptr;
        $$->values.push_back(std::move(*$3));
        DEL($3);
    }
    ;

assignment_list : /* empty */ {
                    $$=new utils::json::Object();
                }
                | str T_COLON value {
                    $$=new utils::json::Object();
                    $$->values.emplace(std::move(*$1),std::move(*$3));
                    DEL($1);
                    DEL($3);
                }/*new*/
                | assignment_list T_COMMA str T_COLON value {
                    $$=$1;
                    $1=nullptr;
                    $$->values.emplace(std::move(*$3),std::move(*$5));
                    DEL($3);
                    DEL($5);
               }
               ;

%%

void utils::json::Parser::error(const std::string &message)
{
   std::cerr<<"Error line "<<json_line_no<<" : "<<message<<std::endl;; 
}
 
/*Now that we have the Parser declared, we can declare the Scanner and implement the yylex function*/
#include <utils/json/Scanner.hpp>
#include <utils/json/Driver.hpp>
static int yylex(utils::json::Parser::semantic_type *yylval,utils::json::Scanner& scanner)
{
    return scanner.yylex(yylval);
}
