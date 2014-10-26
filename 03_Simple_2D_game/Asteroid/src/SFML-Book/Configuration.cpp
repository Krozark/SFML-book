#include <SFML-Book/Configuration.hpp>
#include <SFML-Book/Player.hpp> //Player
#include <SFML-Book/random.hpp> //rand_init

namespace book
{
    ResourceManager<sf::Texture,int> Configuration::textures;
    ActionMap<int> Configuration::player_inputs;
    int Configuration::score;
    int Configuration::level;
    int Configuration::lives;
    book::Player* Configuration::player = nullptr;

    void Configuration::initialize()
    {
        initTextures();
        initPlayerInputs();

        rand_init();
        score = 0;
        level = 1;
        lives = 3;
    }

    void Configuration::initTextures()
    {
        textures.load(Textures::Player,"media/Player/Ship.png");
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

    void Configuration::initPlayerInputs()
    {
        player_inputs.map(PlayerInputs::Up,Action(sf::Keyboard::Up));
        player_inputs.map(PlayerInputs::Right,Action(sf::Keyboard::Right));
        player_inputs.map(PlayerInputs::Left,Action(sf::Keyboard::Left));
        player_inputs.map(PlayerInputs::Shoot,Action(sf::Keyboard::Space));
    }
}
