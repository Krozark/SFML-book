#ifndef BOOK_WORLD_HPP
#define BOOK_WORLD_HPP

namespace book
{
    class World
    {
        public:
            World();
            World(const World&) = delete;
            World& operator=(const World&) = delete;

        protected:

        private:
    };
}
#endif