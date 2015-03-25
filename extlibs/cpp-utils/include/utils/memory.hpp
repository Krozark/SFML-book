#ifndef UTILS_MEMORY_HPP
#define UTILS_MEMORY_HPP

#include <vector>

namespace utils
{
    namespace memory
    {
        class VPool
        {
            public:
                VPool(const VPool&) = delete;
                VPool& operator=(const VPool&) = delete;

                VPool(VPool&&) = default;
                VPool& operator=(VPool&&) = default;

                VPool();
                virtual ~VPool();

                std::size_t size()const;
                void resize(std::size_t size);
                
                bool isSet(std::size_t index)const;

                template<typename T>
                T& at(std::size_t index)const;


                template<typename T>
                void erase(std::size_t index);

                template<typename T,typename ... Args>
                void emplace(std::size_t index,Args&& ... args);

                template<typename T>
                class iterator
                {
                    public:
                        iterator(std::size_t index,const VPool& pool);
                        
                        bool operator !=(const iterator<T>& other);
                        void operator ++();
                        T& operator*()const;
                        T& data()const;
                        std::size_t index()const;

                    private:
                        std::size_t _index;
                        const VPool& _pool;
                };

            protected:
                template<typename T> friend class iterator;
                std::vector<void *> _memory;
        };
    
        template<typename T>
        class Pool : public VPool
        {
            public:
                Pool(const Pool&) = delete;
                Pool& operator=(const Pool&) = delete;

                Pool(Pool&&) = default;
                Pool& operator=(Pool&&) = default;

                Pool();
                virtual ~Pool();

                T& at(std::size_t index)const;

                void erase(std::size_t index);

                template<typename ... Args>
                void emplace(std::size_t index,Args&& ... args);

                VPool::iterator<T> begin()const;
                VPool::iterator<T> end()const;

        };
    }
}
#include <utils/memory.tpl>
#endif
