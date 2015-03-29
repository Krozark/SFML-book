#include <M2MFilter.hpp>

namespace orm
{
    
    M2MFilter::M2MFilter()
    {
    }
    
    template<typename RELATED,typename T>
    Filter<RELATED,T>::~Filter()
    {
    };
}
