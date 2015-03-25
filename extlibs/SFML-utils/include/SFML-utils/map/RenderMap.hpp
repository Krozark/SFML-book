#ifndef SFUTILS_MAP_RENDERMAP_HPP
#define SFUTILS_MAP_RENDERMAP_HPP

namespace sfutils
{
    namespace map
    {
        class RenderMap : 
        {
            public:
                RenderMap(const RenderMap&) = delete;
                RenderMap& operator=(const RenderMap&) = delete;

                RenderMap(const VMap& map);

            protected:

            private:
                const VMap& _map;
        };
    }
}
#endif
