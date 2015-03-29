#ifndef ORM_OP_HPP
#define ORM_OP_HPP

#include <string>

namespace orm
{
    /**
     * \brief Stor the operator values for filter and ordering
     */
    class op
    {
        public:
            //filter
            static const std::string exact;
            static const std::string iexact;
            static const std::string contains;
            static const std::string icontains;
            static const std::string regex;
            static const std::string iregex;
            static const std::string gt;
            static const std::string gte;
            static const std::string lt;
            static const std::string lte;
            static const std::string startswith;
            static const std::string endswith;
            static const std::string istartswith;
            static const std::string iendswith;
            //ordering
            static const std::string random;
            static const char        asc;
            static const char        desc;
    };
}
#endif
