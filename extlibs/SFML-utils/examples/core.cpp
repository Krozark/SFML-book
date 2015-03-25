#include <SFML-utils/Core.hpp>

enum Textures{
    Minotor
};

int main(int argc,char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(600,800),"Example core");

    sfutils::ResourceManager<sf::Texture,int> textures; 
    textures.load(Minotor,"media/img/eye.png");

    sfutils::Animation walkLeft(&textures.get(Minotor));
    walkLeft.addFramesLine(4,2,0);

    sfutils::Animation walkRight(&textures.get(Minotor));
    walkRight.addFramesLine(4,2,1);

    sfutils::AnimatedSprite sprite(&walkLeft,sfutils::AnimatedSprite::Playing,sf::seconds(0.1));

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time delta = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float speed = 50;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            sprite.setAnimation(&walkLeft);
            sprite.play();
            sprite.move(-speed*delta.asSeconds(),0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            sprite.setAnimation(&walkRight);
            sprite.play();
            sprite.move(speed*delta.asSeconds(),0);
        }
        else
        {
            //sprite.pause();
        }


        window.clear();
        
        sprite.update(delta);
        window.draw(sprite);

        //equivalent to : window.draw(frame);

        window.display();
    }

    return 0;
};
