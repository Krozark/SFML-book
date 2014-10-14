#include <utility>

namespace book
{
    template<typename ... Args>
    void Player::setPosition(Args&& ... args)
    {
        _shape.setPosition(std::forward<Args>(args)...);
    }
}
