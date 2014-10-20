#include <utility>

namespace book
{
    template<typename ... Args>
    void Player::setPosition(Args&& ... args)
    {
        _ship.setPosition(std::forward<Args>(args)...);
    }
}
