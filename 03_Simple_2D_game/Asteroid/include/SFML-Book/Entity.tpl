#include <utility> //forward
namespace book
{
    template<typename ... Args>
    void Entity::setPosition(Args&& ... args)
    {
        _sprite.setPosition(std::forward<Args>(args)...);
    }
}
