#include <sstream>

namespace utils
{
namespace string
{
    template<typename T>
    std::string join(const std::string& del,const std::vector<T>& datas,bool reverse)
    {
        std::stringstream ss;
        const unsigned int _size = datas.size();
        if(reverse)
        {
            if(_size > 0)
                ss<<datas[_size-1];
            for(int i=_size-2;i>=0;--i)
                ss<<del<<datas[i];
        }
        else
        {
            if(_size > 0)
                ss<<datas[0];
            for(unsigned int i=1;i<_size;++i)
                ss<<del<<datas[i];
        }

        return ss.str();
    }

    template<typename T>
    void __join_helper(std::stringstream& out,const std::string& del,const T& a)
    {
        out<<a;
    }

    template<typename T,typename U,typename ... Args>
    void __join_helper(std::stringstream& out,const std::string& del,const T& a,const U& b,const Args& ... args)
    {
        out<<a<<del;
        __join_helper(out,del,b,args ...);
    }

    template<typename ... Args>
    inline std::string join(const std::string& del,const Args& ... args)
    {
        std::stringstream ss;
        __join_helper(ss,del,args...);
        return ss.str();
    }
}
}
