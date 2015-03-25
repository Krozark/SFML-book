#include <utils/string.hpp>
#include <cstring>

namespace utils
{
namespace string
{
    std::vector<std::string> split(const std::string& string, const std::string& del)
    {
        size_t first = 0,
               second = 0,
               end = string.size(),
               len = del.size();
        std::vector<std::string> tokens;

        while ((second = string.find(del,first)) != (std::string::npos))
        {
            size_t dif = second - first;
            if (dif)
                tokens.push_back(string.substr(first,dif));
            first = second + len;
        }
        if (first != end)
            tokens.push_back(string.substr(first));
        return tokens;
    }

    void replace(std::string& source,const std::string& find,const std::string& rep)
    {
        for(std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
        {
            source.replace(i, find.length(), rep);
            i += rep.length() - find.length() + 1;
        }
    }

    bool startswith(const std::string& comp,const std::string& with)
    {
        auto c = comp.size();
        auto w = with.size();
        return (w <= c
                and ::strncmp(with.c_str(),comp.c_str(),w)== 0);
    }

    bool endswith(const std::string& comp,const std::string& with)
    {
        auto c = comp.size();
        auto w = with.size();
        return (w <= c
                and ::strncmp(with.c_str(),comp.c_str()+c-w,w)== 0);
    }
}
}
