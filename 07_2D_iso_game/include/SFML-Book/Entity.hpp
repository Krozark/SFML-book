#ifndef BOOK_ENTITY_HPP
#define BOOK_ENTITY_HPP

namespace book
{
    class Entity
    {
        public:
            Entity();
            Entity(const Entity&) = delete;
            Entity& operator=(const Entity&) = delete;

        protected:

        private:
    };
}
#endif