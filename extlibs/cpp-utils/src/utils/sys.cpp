#include <utils/sys.hpp>
#include <utils/string.hpp>

#include <stdexcept>

#ifdef _WIN32
    #include <windows.h>
    char *realpath(const char *path, char resolved_path[PATH_MAX]);
#elif __unix || __unix__
    #include <unistd.h>
    #include <ftw.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

namespace utils
{
namespace sys
{
    #ifdef _WIN32
    char *realpath(const char *path, char resolved_path[PATH_MAX]);
    #endif

    std::string whereis(const std::string& name)
    {
        //compute path dirs vector
        std::vector<std::string> paths = utils::string::split(std::string(::getenv("PATH")),
        #ifdef _WIN32 //_WIN64
        ";"
        #else
        ":"
        #endif
        );

        for(std::string& bpath : paths)
        {
            std::string fpath = bpath;
            if(bpath.size() > 1)
            {
                #ifdef _WIN32 //_WIN64
                if(bpath[bpath.size()-1] != '\\')
                    fpath += '\\';
                #else
                if(bpath[bpath.size()-1] != '/')
                    fpath += '/';
                #endif
            }
            fpath += name;
            if(utils::sys::file::exists(fpath))
                return fpath;
        }
        return {};
    }

    //Library
    Library::Library(const std::string& name) : _name(name),lib(nullptr)
    {
        #ifdef _WIN32
        if(not utils::string::endswith(_name,".dll"))
            _name+=".dll";
        #else
        if(not utils::string::endswith(_name,".so"))
            _name+=".so";
        #endif
    }

    Library::~Library()
    {
        if(lib)
            close();
    }

    bool Library::load()
    {
        #ifdef _WIN32 //_WIN64
        lib = ::LoadLibrary(_name.c_str());
        if (lib == nullptr)
        {
            utils::log::error("utils:sys::Library::load","Unable to load ",_name);
            return false;
        }
        #elif __linux //|| __unix //or __APPLE__
        lib = ::dlopen(_name.c_str(), RTLD_LAZY);
        char* err = ::dlerror();
        if (lib == nullptr or err)
        {
            utils::log::error("utils:sys::Library::load","Unable to load ",_name,err);
            return false;
        }
        #endif
        return true;
    }

    void Library::close()
    {

        //clear all linked functions
        for(auto& c : funcs)
            delete c.second;
        funcs.clear();

        //delete the lib
        #ifdef _WIN32 //_WIN64
        ::FreeLibrary(lib);
        #elif __linux
        ::dlclose(lib);
        ::dlerror();
        #endif
        lib = nullptr;

    }

    void* Library::get_f(const std::string& name)const
    {
        void* f = nullptr;
        #ifdef _WIN32 //_WIN64
        f = (void*)::GetProcAddress(lib,name.c_str());
        if(f == nullptr)
        {
            utils::log::error("utils:sys::Library::get_f","Unable to load function",name);
        }
        #elif __linux //|| __unix //or __APPLE__
        f = ::dlsym(lib,name.c_str());
        char* err = ::dlerror();
        if(f == nullptr or err)
        {
            f = nullptr;
            utils::log::error("utils:sys::Library::get_f","Unable to load function",name,err);
        }
        #endif
        return f;
    }

    utils::func::VFunc* Library::operator[](const std::string& name)
    {
        auto value = funcs.find(name);
        if(value != funcs.end())
            return value->second;
        return nullptr;
    }

    const std::string Library::name()const
    {
        return _name;
    }

    //Compiler
    Compiler::Compiler() : _output("./out")
    {
        #ifdef _WIN32 //_WIN64
        auto comp_list = {"mingw32-g++.exe","clang.exe"};
        #else
        auto comp_list = {"g++","clang"};
        #endif

        for(const std::string& c : comp_list)
        {
            std::string path = sys::whereis(c);
            if(not path.empty())
            {
                _name = c;
                break;
            }
        }
        if(_name.empty())
            throw std::runtime_error("no compilater "
            #ifdef _WIN32 //_WIN64
            "mingw-g++.exe or clang.exe"
            #else
            "g++ or clang"
            #endif
            " find");
    }

    Compiler::Compiler(const std::string& name) : _output("./out")
    {
        std::string path = sys::whereis(name);
        if(path.empty())
            throw std::runtime_error(name);
        _name = path;
    }

    Compiler& Compiler::output(const std::string& out)
    {
        if(not out.empty())
        {
            #ifdef _WIN32 //_WIN64
            if(string::startswith(out,".\\"))
                _output = out;
            else
                _output = ".\\"+out;
            #else
            if(string::startswith(out,"./"))
                _output = out;
            else
                _output = "./"+out;
            #endif
        }

        return *this;
    }


    Library Compiler::get() const
    {
        //TODO build in thread::Pool[0.-1]
        for(const std::string& u : make_cmds())
        {
            utils::log::info("utils:sys::Compiler::get","system("+u+")");
            int res = ::system(u.c_str());
            if(res == -1)
            {
                utils::log::error("utils:sys::Compiler::get","failed to make sytem call");
                throw std::runtime_error("fork failed");
            }
            else if(res != 0)
            {
                utils::log::error("utils:sys::Compiler::get","the command return the error code:",res);
                throw std::runtime_error("fork failed");
            }

        }
        for(const std::string& f: _inputs)
            sys::file::rm(f+".o");
        return {_output};
        /*+
        #ifdef _WIN32
        ".dll"
        #else
        ".so"
        #endif
        ;*/
    }

    std::ostream& operator<<(std::ostream& output,const Compiler& self)
    {
        for(const std::string& u : self.make_cmds())
            output<<u<<std::endl;
        return output;
    }



    std::vector<std::string> Compiler::make_cmds() const
    {
        std::vector<std::string> res;
        //compile as .o
        unsigned int _size = _inputs.size();
        for(unsigned int i=0;i<_size;++i)
        {
            std::string tmp = _name + " -fpic ";

            unsigned int _s = _flags.size();
            for(unsigned int i=0;i<_s;++i)
                tmp+=" "+_flags[i];

            tmp +=" -x c++ -c \"" +_inputs[i]+"\" -o \""+_inputs[i]+".o\"";

            res.push_back(std::move(tmp));
        }
        //compile .o as .so/.dll
        {
            std::string tmp = _name + " -shared -o "+_output+
            #ifdef _WIN32
            ".dll";
            #else
            ".so";
            #endif

            for(unsigned int i=0;i<_size;++i)
                tmp+= " \""+_inputs[i]+".o\"";

            unsigned int _s = _links.size();
            if(_s>0)
            {
                for(unsigned int i=0;i<_s;++i)
                    tmp += " -l"+_links[i];
            }

            res.push_back(std::move(tmp));
        }

        return res;
    }

    namespace dir
    {
        int create(const std::string& dirpath,const int permissions)
        {
            int res = 1; //0 => error, 1 => created, 2 => already exist
            auto sp = string::split(dirpath,"/");


            std::string current;
            if(dirpath.size() > 0 and dirpath[0] == '/')
                current = "/";
            const unsigned int _size = sp.size();
            for(unsigned int i=0; i<_size and res != 0;++i)
            {

                current += sp[i] + "/";

                #if __WIN32
                res = ::mkdir(current.c_str());
                #else
                res = ::mkdir(current.c_str(), permissions);
                #endif

                if(res == 0)
                    res = 1;
                else if(errno == EEXIST)
                    res = 2;
                else
                    res = 0;
            }
            return res;
        }

        std::list<std::string> list_files(const std::string& dirpath)
        {
            DIR *curDir;
            std::list<std::string> res;

            if ((curDir = opendir(dirpath.c_str())) == NULL)
                return res;

            dirent *curEntry =readdir(curDir);
            while (curEntry != NULL)
            {
                #if _WIN32
                DWORD dwAttrib = GetFileAttributes(curEntry->d_name);
                if (dwAttrib != INVALID_FILE_ATTRIBUTES && not (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
                #else
                if(curEntry->d_type == DT_REG)

                #endif // _WIN32
                    res.push_back(curEntry->d_name);
                curEntry =readdir(curDir);
            }
            ::closedir(curDir);
            return res;
        }

        std::list<std::string> list_dirs(const std::string& dirpath)
        {
            DIR *curDir;
            std::list<std::string> res;

            if ((curDir = opendir(dirpath.c_str())) == NULL)
                return res;

            dirent *curEntry =readdir(curDir);
            while (curEntry != NULL)
            {
                #if _WIN32
                DWORD dwAttrib = GetFileAttributes(curEntry->d_name);
                if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)
                #else
                if(curEntry->d_type == DT_DIR
                #endif
                   and std::string(curEntry->d_name) != ".."
                   and std::string(curEntry->d_name) != ".")
                    res.push_back(curEntry->d_name);
                curEntry =readdir(curDir);
            }
            ::closedir(curDir);
            return res;
        }


        bool rm(const std::string& path,bool recusive)
        {
            bool res;
            if(not recusive)
            {
                #if _WIN32
                res = RemoveDirectory(path.c_str());
                #endif // _WIN32
                #if __unix__
                res = ::rmdir(path.c_str()) == 0;
                #endif
            }
            else
            {
                #if _WIN32
                res = RemoveDirectory(path.c_str()); ///< todo rewove directory recursivjy
                #else
                auto f = [](const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) -> int
                {
                    int rv;
                    switch(typeflag)
                    {
                        case FTW_F:
                            rv = ::unlink(fpath);break;
                        case FTW_D:
                        case FTW_DP:
                            rv = ::rmdir(fpath);break;
                        default:
                            rv = ::remove(fpath);break;
                    }

                    if (rv)
                        ::perror(fpath);
                    return rv;
                };

                res = ::nftw(path.c_str(),f, 64, FTW_DEPTH | FTW_PHYS) == 0;
                #endif // _WIN32
            }
            return res;
        }

        bool rm_if_empty(const std::string& path,bool recusive)
        {
            bool res;

            #if _WIN32
            res = RemoveDirectory(path.c_str());
            #endif // _WIN32
            #if __unix__
            res = ::rmdir(path.c_str()) == 0;
            #endif

            return res;
        }

        std::string pwd()
        {
            #if _WIN32
            char path[256];
            ::GetCurrentDirectory(256,path);
            std::string res(path);
            #else
            char* path = ::get_current_dir_name();
            std::string res(path);
            ::free(path);
            #endif
            return res;
        }

        std::string abs_path(const std::string& relative_path)
        {
            char my_path[relative_path.size() + 1];
            ::strcpy(my_path,relative_path.c_str());
            char *resolved_path = realpath(my_path,nullptr);
            std::string res =  resolved_path;
            ::free(resolved_path);
            return res;
        }

    }

    namespace file
    {
        bool rm(const std::string& path)
        {
            #if _WIN32
            return false; ///< todo
            #else
            return ::unlink(path.c_str()) == 0;
            #endif
        }

        bool exists(const std::string& name)
        {
            if (FILE *file = fopen(name.c_str(), "rb"))
            {
                fclose(file);
                return true;
            }
            return false;
        }

        bool touch(const std::string& path)
        {
            //build dir tree
            #ifdef _WIN32 //_WIN64
            std::string file_path = path;
            utils::string::replace(file_path,"\\","/");
            #else
            const std::string& file_path = path;
            #endif
            std::vector<std::string> dirs = utils::string::split(file_path,"/");
            if(dirs.size()>1)
                dirs.pop_back();
            std::string dir_path = "/"+utils::string::join("/",dirs);
            if(not dir::create(dir_path))
                return false;

            //create file
            if (FILE *file = fopen(file_path.c_str(), "ab"))
            {
                fclose(file);
                return true;
            }
            return false;

        }


    }

#if _WIN32
    #include <stdlib.h>
    #include <limits.h>
    #include <errno.h>
    #include <sys/stat.h>
    char *realpath(const char *path, char resolved_path[PATH_MAX])
        {
          char *return_path = 0;

          if (path) //Else EINVAL
          {
            if (resolved_path)
            {
              return_path = resolved_path;
            }
            else
            {
              //Non standard extension that glibc uses
              return_path = (char*)malloc(PATH_MAX);
            }

            if (return_path) //Else EINVAL
            {
              //This is a Win32 API function similar to what realpath() is supposed to do
              size_t size = GetFullPathNameA(path, PATH_MAX, return_path, 0);

              //GetFullPathNameA() returns a size larger than buffer if buffer is too small
              if (size > PATH_MAX)
              {
                if (return_path != resolved_path) //Malloc'd buffer - Unstandard extension retry
                {
                  size_t new_size;

                  free(return_path);
                  return_path = (char*)malloc(size);

                  if (return_path)
                  {
                    new_size = GetFullPathNameA(path, size, return_path, 0); //Try again

                    if (new_size > size) //If it's still too large, we have a problem, don't try again
                    {
                      free(return_path);
                      return_path = 0;
                      errno = ENAMETOOLONG;
                    }
                    else
                    {
                      size = new_size;
                    }
                  }
                  else
                  {
                    //I wasn't sure what to return here, but the standard does say to return EINVAL
                    //if resolved_path is null, and in this case we couldn't malloc large enough buffer
                    errno = EINVAL;
                  }
                }
                else //resolved_path buffer isn't big enough
                {
                  return_path = 0;
                  errno = ENAMETOOLONG;
                }
              }

              //GetFullPathNameA() returns 0 if some path resolve problem occured
              if (!size)
              {
                if (return_path != resolved_path) //Malloc'd buffer
                {
                  free(return_path);
                }

                return_path = 0;

                //Convert MS errors into standard errors
                switch (GetLastError())
                {
                  case ERROR_FILE_NOT_FOUND:
                    errno = ENOENT;
                    break;

                  case ERROR_PATH_NOT_FOUND: case ERROR_INVALID_DRIVE:
                    errno = ENOTDIR;
                    break;

                  case ERROR_ACCESS_DENIED:
                    errno = EACCES;
                    break;

                  default: //Unknown Error
                    errno = EIO;
                    break;
                }
              }

              //If we get to here with a valid return_path, we're still doing good
              if (return_path)
              {
                struct stat stat_buffer;

                //Make sure path exists, stat() returns 0 on success
                if (stat(return_path, &stat_buffer))
                {
                  if (return_path != resolved_path)
                  {
                    free(return_path);
                  }

                  return_path = 0;
                  //stat() will set the correct errno for us
                }
                //else we succeeded!
              }
            }
            else
            {
              errno = EINVAL;
            }
          }
          else
          {
            errno = EINVAL;
          }

          return return_path;
        }
#endif
}
}
