namespace utils
{
    namespace memory
    {
        ///////////////// VPOOL ///////////////
        
        template<typename T>
        T& VPool::at(std::size_t index)const
        {
            return *static_cast<T*>(_memory.at(index));
        }

        template<typename T>
        void VPool::erase(std::size_t index)
        {
            delete static_cast<T*>(_memory.at(index));
            _memory[index] = nullptr;
        }

        template<typename T,typename ... Args>
        void VPool::emplace(std::size_t index,Args&& ... args)
        {
            delete static_cast<T*>(_memory.at(index));
            _memory[index] = new T(args...);
        }


        ///////////// ITERATOR ///////

        template<typename T>
        VPool::iterator<T>::iterator(std::size_t index,const VPool& pool) : _index(index), _pool(pool)
        {
        }
        
        template<typename T>
        bool VPool::iterator<T>::operator !=(const iterator<T>& other)
        {
            return _index != other._index or &_pool != &other._pool;
        }

        template<typename T>
        void VPool::iterator<T>::operator ++()
        {
            auto size = _pool._memory.size();
            ++_index;
            while(_index < size and _pool._memory[_index] == nullptr)
                ++_index;
        }

        template<typename T>
        T& VPool::iterator<T>::operator*()const
        {
            return _pool.at<T>(_index);
        }

        template<typename T>
        T& VPool::iterator<T>::data()const
        {
            return _pool.at<T>(_index);
        }

        template<typename T>
        std::size_t VPool::iterator<T>::index()const
        {
            return _index;
        }

        //////////// POOL //////////////////

        template<typename T>
        Pool<T>::Pool()
        {
        }

        template<typename T>
        T& Pool<T>::at(std::size_t index)const
        {
            return VPool::at<T>(index);
        }

        template<typename T>
        void Pool<T>::erase(std::size_t index)
        {
            VPool::erase<T>(index);
        }

        template<typename T>
        template<typename ... Args>
        void Pool<T>::emplace(std::size_t index,Args&& ... args)
        {
            VPool::emplace<T>(index,args ...);
        }

        template<typename T>
        Pool<T>::~Pool()
        {
            const std::size_t size = _memory.size();
            for(std::size_t i=0;i<size;++i)
                delete static_cast<T*>(_memory[i]);
            _memory.clear();
        }

        template<typename T>
        VPool::iterator<T> Pool<T>::begin()const
        {
            std::size_t index = 0;
            std::size_t size = _memory.size();

            while(index < size and _memory[index] ==nullptr)
                ++index;

            return VPool::iterator<T>(index,*this);
        }

        template<typename T>
        VPool::iterator<T> Pool<T>::end()const
        {
            return VPool::iterator<T>(_memory.size(),*this);
        }

    }
}
