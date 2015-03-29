#ifndef ORM_DEBUG_HPP
#define ORM_DEBUG_HPP

#define ORM_DEFAULT_MAX_DEPTH 1 ///< maximum depth
#define ORM_ALLOW_EXCEPTION 1 ///< let them ?

/**********************************
 ******* DEBUG MOD ****************
 *********************************/
#define ORM_DEGUG_NO 0 ///< no debug print
#define ORM_DEBUG_SQL 1<<1 ///< print sql
#define ORM_DEBUG_REGISTER 1<<2 ///< print regiter of class
#define ORM_DEBUG_GET_OBJ 1<<3 ///< print object construction
#define ORM_DEBUG_GET_ATTR 1<<4 ///< print attr construction (verbose)
#define ORM_DEBUG_CREATE_TABLE 1<<5 //< print a msg when a table is create
#define ORM_DEBUG_DROP_TABLE 1<<6 //< print a msg when a table is drop
#define ORM_DEBUG_TRUNCATE_TABLE 1<<7 //< print a msg when a table is truncate

#define ORM_DEBUG_FULL (0xFFFF) ///< all debug mods

//#define ORM_DEBUG (ORM_DEBUG_REGISTER)
/*#define ORM_DEBUG (ORM_DEBUG_REGISTER \
                   | ORM_DEBUG_SQL \
                   | ORM_DEBUG_CREATE_TABLE \
                   | ORM_DEBUG_DROP_TABLE \
                   | ORM_DEBUG_TRUNCATE_TABLE \
                   )*/
//#define ORM_DEBUG (ORM_DEBUG_SQL | ORM_DEBUG_REGISTER)
#define ORM_DEBUG (ORM_DEBUG_REGISTER)
//#define ORM_DEBUG (ORM_DEBUG_FULL) ///<current debug mod

#if ORM_DEBUG > 0
#include <iostream>
#endif

/*******************************
 ******** VEREBOSITY ***********
 ******************************/
#define ORM_VERBOSE 1<<1 ///< Notification
#define ORM_WARNING 1<<2 ///< semi important, could change the running
#define ORM_ERROR   1<<3 ///< critical

//#define ORM_VERBOSITY (ORM_VERBOSE | ORM_WARNING | ORM_ERROR) ///< current verbosity
#define ORM_VERBOSITY (ORM_ERROR) ///< current verbosity

/*** print macros ****/

#if ORM_VERBOSITY & ORM_ERROR
#define ORM_PRINT_ERROR(txt) {std::cerr<<ROUGE<<"[ERROR]("<<__FILE__<<":"<<__LINE__<<") "<<txt<<BLANC<<std::endl;}
#else
#define ORM_PRINT_ERROR(txt) {}
#endif

#if ORM_VERBOSITY & ORM_WARNING
#define ORM_PRINT_WARNING(txt) {std::cerr<<JAUNE<<"[WARNING]("<<__FILE__<<":"<<__LINE__<<") "<<txt<<BLANC<<std::endl;}
#else
#define ORM_PRINT_WARNING(txt) {}
#endif

#if ORM_VERBOSITY & ORM_VERBOSE
#define ORM_PRINT_VERBOSE(txt) {std::cerr<<COMMENTAIRE<<"[VERBOSE]("<<__FILE__<<":"<<__LINE__<<") "<<txt<<BLANC<<std::endl;}
#else
#define ORM_PRINT_VERBOSE(txt) {}
#endif


/**************************
******** COLORS ***********
**************************/


#define ROUGE  	"\033[31m"
#define VERT   	"\033[32m"
#define JAUNE  	"\033[33m"
#define BLEU   	"\033[34m"
#define MAGENTA "\033[35m"
#define LMAGENTA "\033[01;35m"
#define BLEU2 "\033[36m"
#define COMMENTAIRE "\033[31m"
#define BLANC 	"\033[00m"

#endif
