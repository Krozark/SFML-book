#ifndef UTILS_SYS_HPP
#define UTILS_SYS_HPP

#include <string>
#include <list>
#include <vector>
#include <unordered_map>

#include <iostream>

#ifdef _WIN32 //_WIN64
    #include <windows.h>
#elif __linux //|| __unix //or __APPLE__ 
    #include <dlfcn.h>
#else
    #error not defined for this platform
#endif

#include <utils/log.hpp>
#include <utils/functional.hpp>

namespace utils
{
    namespace func{
        class VFunc;
    }
/**
 * \brief a namspace that regroup function for the system
 */
namespace sys
{
    /**
     * \brief search a file in $PATH
     * \return the path where the file was find. if no file find, the value is empty
     */
    std::string whereis(const std::string& filename);
    
    /**
     * \brief A class to load dynamic library
     */
    class Library
    {
        public:
            Library(const Library&)=delete;
            Library& operator=(const Library&)=delete;
            
            Library(Library&&) = default;
            Library& operator=(Library&&) = default;

            /**
             * \param name the library filename (with no .dll/.so extention
             */
            Library(const std::string& name);

            ~Library();

            /**
             * \brief load the library
             * \return true on success
             */
            bool load();

            /**
             * \brief close the library and free the memory.
             * Must be call before the object destruction
             */
            void close();

            /**
             * \brief Load a function from the library by his name
             * \param Ret the return type
             * \param Args the func params
             * \return true on success
             */
            template<typename Ret,typename ... Args>
            bool load_f(const std::string& name);

            /**
             * \return the function pointer of name name. nullptr on error
             */
            void* get_f(const std::string& name)const;
            
            /**
             * \return the loaded function by his name. return nullptr on error
             */
            utils::func::VFunc* operator[](const std::string& name);

            const std::string name()const;

        private:
            std::string _name;///<filename
            std::unordered_map<std::string,utils::func::VFunc*> funcs;///< loaded functions

            #ifdef _WIN32 //_WIN64
            HMODULE lib; ///< lib manager
            #elif __linux
            void* lib; ///< lig manager
            #endif
    };

    /**
     * \brieaf a class that manage system compiler
     */
    class Compiler
    {
        public:
            Compiler(const Compiler&) = default;
            Compiler& operator=(const Compiler&) = default;
            Compiler(Compiler&&) = default;
            Compiler& operator=(Compiler&&) = default;

            /**
             * \brief search for a compiler in the sytstem
             * note : search for linux : g++, clang | win : mingw32-g++.exe, clang.exe
             * \return the first compiler find
             * throw std::runtime_error on error
             */
            Compiler();

            /**
             * \brief search the compiler of the name
             * \param name the compiler name to find
             * \return the compiler
             * throw std::runtime_error on error
             */
            Compiler(const std::string& name);

            /**
             * \brief add input file to compile
             */
            template<typename ... Args>
            Compiler& input(Args&& ... args);
            
            /**
             * \brief set the output lib name (no .so/.dll needed)
             */
            Compiler& output(const std::string& out);

            /**
             * \brief add compiler flags
             */
            template<typename ... Args>
            Compiler& flags(Args&& ... args);

            /**
             * \brief add external liubrary to link with
             */
            template<typename ... Args>
            Compiler& link(Args&& ... args);

            /**
             * \brief run the compilation, and return a Library. You have to load it
             */
            Library get() const;

            /**
             * \brief get the command lines use to build the lib
             */
            friend std::ostream& operator<<(std::ostream& output,const Compiler& self);
        private:
            std::string _name; ///<compiler binary path
            std::vector<std::string> _inputs; ///< files to compile
            std::string _output; //< output lib name
            std::vector<std::string> _flags;///< optionals flags
            std::vector<std::string> _links;///< optional extern libs to link mith


            std::vector<std::string> make_cmds() const; ///< make the cmd to send to the system
    };
    
    /**
     * \brief regroup functions on dir and manipulation
     */
    namespace dir
    {
        /**
         * \brief create a directory.
         * \param dirpath the dir path name
         * \param permissions  (ignored in windows)
         * \return 1 if created, 2 if it was allready exist, 0 if errored
         */
        int create(const std::string& dirpath,const int permissions = 0777);

        /**
         * \brief get file list of a directory
         * \param dirpath the root dir
         * \return the list
         */
        std::list<std::string> list_files(const std::string& path);

        /**
         * \brief get the dir list in a folder
         * \param dirpath the root dir
         * \return the dir list (without . and ..)
         */
        std::list<std::string> list_dirs(const std::string& path);


        /**
         * \brief remove a directory.
         * \param  recusive if true, delete all files on directory inside
         * \return true on success
         */
        bool rm(const std::string& path,bool recusive=false);


        /**
         * \brief remove the directory is empty
         * \brief recusive if true, delete all sub directory that are empty
         * \return true on success
         */
        bool rm_if_empty(const std::string& path,bool recusive=false);

        /**
         * \return the current dir path
         */
        std::string pwd();

        /**
         * \return the real path of
         */
        std::string abs_path(const std::string& relative_path);
    }

    namespace file
    {
        /**
         * \brief remove a file
         * \return true on success
         */
        bool rm(const std::string& path);

        /**
         * \return true if the file file_path exists
         */
        bool exists(const std::string& file_path);

        /**
         * \brief creat a empty file (creat the dir tree)
         * \return true on success
         */
        bool touch(const std::string& file_path);
    }
}
}
#include <utils/sys.tpl>
#endif
