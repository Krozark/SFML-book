#include <SFML-Book/Configuration.hpp>

namespace book
{
    sfutils::ResourceManager<sf::Texture,int> Configuration::textures;
    sfutils::ResourceManager<sfutils::Animation,int> Configuration::animations;

    void Configuration::initialize()
    {
        initTextures();
        initAnimations();
    }

    void Configuration::initTextures()
    {
        textures.load(Textures::Eye,"media/img/eye.png");
    }


    void Configuration::initAnimations()
    {
        animations.load(Animations::EyeLeft,&textures.get(Textures::Eye)).addFramesLine(4,2,0);
        animations.load(Animations::EyeRight,&textures.get(Textures::Eye)).addFramesLine(4,2,1);
    }
}
