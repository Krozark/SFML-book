#include <utils/memory.hpp>

namespace utils
{
    namespace memory
    {
        VPool::VPool()
        {
        }

        VPool::~VPool()
        {
        }

        std::size_t VPool::size()const
        {
            return _memory.size();
        }

        void VPool::resize(std::size_t size)
        {
            _memory.resize(size,nullptr);
        }

        bool VPool::isSet(std::size_t index)const
        {
            return _memory.at(index) != nullptr;
        }
        
    }
}
