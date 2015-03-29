#include <ORM/backends/op.hpp>

namespace orm
{
    const std::string op::exact      = "exact";
    const std::string op::iexact     = "iexact";
    const std::string op::contains   = "contains" ;
    const std::string op::icontains  = "icontains";
    const std::string op::regex      = "regex";
    const std::string op::iregex     = "iregex";
    const std::string op::gt         = "gt";
    const std::string op::gte        = "gte";
    const std::string op::lt         = "lt";
    const std::string op::lte        = "lte";
    const std::string op::startswith = "startswith";
    const std::string op::endswith   = "endswith";
    const std::string op::istartswith= "istartswith";
    const std::string op::iendswith  = "iendswith";

    const std::string op::random     = "?";
    const char        op::asc        = '+';
    const char        op::desc       = '-';
}
