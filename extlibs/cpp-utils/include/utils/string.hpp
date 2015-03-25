#ifndef UTILS_STRING_HPP
#define UTILS_STRING_HPP

#include <string>
#include <vector>

namespace utils
{
/**
 * \brief a namspace for string manipulations
 */
namespace string
{
    /**
     * \brief split a string in multiple sub string
     * \param string base to split
     * \param del the delemiteur
     * \return a vector that contain the sub string
     */
    std::vector<std::string> split(const std::string& string,const std::string& del);

    /**
     * \brief find and replace
     * \param source the source string to change
     * \param find the separator
     * \param replace find is replace by it
     */
    void replace(std::string& source,const std::string& find,const std::string& rep);

    /**
     * \brief like the python join
     * \param  del the delimitor to use
     * \param datas the datas to use for join. It must have a std::stringstream& operator<<(const T&,std::stringstream&)
     * \param reverse reverse the order of join (end to begin)
     */
    template<typename T>
    std::string join(const std::string& del,const std::vector<T>& datas,bool reverse=false);

    /**
     * \brief like the python join
     * \param  del the delimitor to use
     * \param args create a string using std::sstream. It must have a std::stringstream& operator<<(const T&,std::stringstream&)
     */
    template<typename ... Args>
    inline std::string join(const std::string& del,const Args& ... args);

    /**
     * \return true if comp starts with with
     */
    bool startswith(const std::string& comp,const std::string& with);

    /**
     * \return true if comp ends with with
     */
    bool endswith(const std::string& comp,const std::string& with);
}
}
#include <utils/string.tpl>
#endif
