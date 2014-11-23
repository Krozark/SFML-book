#ifndef BOOK_RESOURCEMANAGER_HPP
#define BOOK_RESOURCEMANAGER_HPP

#include <unordered_map> //unordered_map
#include <string> //string
#include <memory> //unique_ptr

#include <SFML/Audio.hpp> //sf::Music

namespace book
{
    template<typename RESOURCE,typename IDENTIFIER = int>
    class ResourceManager
    {
        public:
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;

            ResourceManager() = default;

            template<typename ... Args>
            void load(const IDENTIFIER& id,Args&& ... args);

            RESOURCE& get(const IDENTIFIER& id)const;

        private:
            std::unordered_map<IDENTIFIER,std::unique_ptr<RESOURCE>> _map;
    };

    template<typename IDENTIFIER>
    class ResourceManager<sf::Music,IDENTIFIER>
    {
        public:
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;

            ResourceManager() = default;

            template<typename ... Args>
            void load(const IDENTIFIER& id,Args&& ... args);

            sf::Music& get(const IDENTIFIER& id)const;

        private:
            std::unordered_map<IDENTIFIER,std::unique_ptr<sf::Music>> _map;
    };


}
#include <SFML-Book/ResourceManager.tpl>

#endif
