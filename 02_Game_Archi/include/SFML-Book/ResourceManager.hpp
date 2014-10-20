#ifndef BOOK_RESOURCEMANAGER_HPP
#define BOOK_RESOURCEMANAGER_HPP

#include <unordered_map> //unordered_map
#include <string> //string

namespace book
{
    template<typename T>
    class ResourceManager
    {
        public:
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;

            ResourceManager();

            void load(int id,const std::string& filename);
            T& get(int id);

        private:
            std::unordered_map<int,T> _map;
    };
}
#include <SFML-Book/ResourceManager.tpl>

#endif
