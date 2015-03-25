#include <SFML-utils/core/Animation.hpp>

namespace sfutils
{
    Animation::Animation(sf::Texture* texture) : _texture(texture)
    {
    }

    Animation::~Animation()
    {
    }

    void Animation::setTexture(sf::Texture* texture)
    {
        _texture = texture;
    }

    sf::Texture* Animation::getTexture()const
    {
        return _texture;
    }
    
    Animation& Animation::addFrame(const sf::IntRect& rect)
    {
        _frames.emplace_back(rect);
        return *this;
    }

    Animation& Animation::addFramesLine(int number_x,int number_y,int line)
    {
        const sf::Vector2u size = _texture->getSize();
        const float delta_x = size.x / float(number_x);
        const float delta_y = size.y / float(number_y);

        for(int i = 0;i<number_x;++i)
            addFrame(sf::IntRect(i*delta_x,
                                 line*delta_y,
                                 delta_x,
                                 delta_y));
        return *this;
    }

    Animation& Animation::addFramesColumn(int number_x,int number_y,int column)
    {
        const sf::Vector2u size = _texture->getSize();
        const float delta_x = size.x / float(number_x);
        const float delta_y = size.y / float(number_y);

        for(int i = 0;i<number_y;++i)
            addFrame(sf::IntRect(column*delta_x,
                                 i*delta_y,
                                 delta_x,
                                 delta_y));
        return *this;
    }

    size_t Animation::size()const
    {
        return _frames.size();
    }

    const sf::IntRect& Animation::getRect(size_t index)const
    {
        return _frames[index];
    }
}
