#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Player.hpp> //Player
#include <SFML-Book/random.hpp> //rand_init

namespace book
{
    ResourceManager<sf::Texture,int> Configuration::textures;
     ResourceManager<sf::Font,int> Configuration::fonts;
    ActionMap<int> Configuration::player_inputs;
    int Configuration::level;
    int Configuration::lives;

    book::Player* Configuration::player = nullptr;

    int Configuration::_score;
    sf::Text   Configuration::_txt_score;
    sf::Sprite Configuration::_spr_life;

    void Configuration::initialize()
    {
        initTextures();
        initFonts();
        initPlayerInputs();

        rand_init();
        level = 1;
        lives = 3;

        _score = 0;
        _txt_score.setFont(fonts.get(Fonts::Gui));
        _txt_score.setCharacterSize(24);
        _txt_score.setString("0");

        _spr_life.setTexture(textures.get(Textures::PlayerLife));
    }

    void Configuration::addScore(int s)
    {
        _score += s;
        _txt_score.setString(std::to_string(_score));
    }

    int Configuration::getScore()
    {
        return _score;
    }

    void Configuration::draw(sf::RenderTarget& target)
    {
        target.draw(_txt_score);
        for(int i = 0;i< lives;++i)
        {
            _spr_life.setPosition(40*i,40);
            target.draw(_spr_life);
        }
    }

    void Configuration::initTextures()
    {
        //player
        textures.load(Textures::Player,"media/Player/Ship.png");
        textures.load(Textures::PlayerLife,"media/Player/life.png");
        //saucers
        textures.load(Textures::BigSaucer,"media/Saucer/Big.png");
        textures.load(Textures::SmallSaucer,"media/Saucer/Small.png");
        //meteors
        textures.load(Textures::BigMeteor1,"media/Meteor/Big1.png");
        textures.load(Textures::BigMeteor2,"media/Meteor/Big2.png");
        textures.load(Textures::BigMeteor3,"media/Meteor/Big3.png");
        textures.load(Textures::BigMeteor4,"media/Meteor/Big4.png");

        textures.load(Textures::MediumMeteor1,"media/Meteor/Medium1.png");
        textures.load(Textures::MediumMeteor2,"media/Meteor/Medium2.png");

        textures.load(Textures::SmallMeteor1,"media/Meteor/Small1.png");
        textures.load(Textures::SmallMeteor2,"media/Meteor/Small2.png");
        textures.load(Textures::SmallMeteor3,"media/Meteor/Small3.png");
        textures.load(Textures::SmallMeteor4,"media/Meteor/Small4.png");
        //lasers
        textures.load(Textures::ShootPlayer,"media/Shoot/Player.png");
        textures.load(Textures::ShootSaucer,"media/Shoot/Saucer.png");
    }

    void Configuration::initFonts()
    {
        fonts.load(Fonts::Gui,"media/font/trs-million.ttf");
    }

    void Configuration::initPlayerInputs()
    {
        player_inputs.map(PlayerInputs::Up,Action(sf::Keyboard::Up));
        player_inputs.map(PlayerInputs::Right,Action(sf::Keyboard::Right));
        player_inputs.map(PlayerInputs::Left,Action(sf::Keyboard::Left));
        player_inputs.map(PlayerInputs::Shoot,Action(sf::Keyboard::Space));
    }
}
