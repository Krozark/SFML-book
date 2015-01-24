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
        textures.load(TexMain,"media/skins/main.png");
        textures.load(TexEye,"media/skins/eye.png");
    }


    void Configuration::initAnimations()
    {
        animations.load(AnimMain,&textures.get(TexMain)).addFramesLine(5,1,0);
        animations.load(AnimEyeLeft,&textures.get(TexEye)).addFramesLine(4,2,0);
        animations.load(AnimEyeRight,&textures.get(TexEye)).addFramesLine(4,2,1);
    }
}
