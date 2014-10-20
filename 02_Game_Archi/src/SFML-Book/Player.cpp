#include <SFML-Book/Player.hpp>
#include <SFML-Book/ActionMap.hpp>
#include <cmath> //sin, cos

namespace book
{
    ActionMap<int> Player::_player_inputs;

    Player::Player() : ActionTarget(_player_inputs)
                       ,_is_moving(false)
                       ,_rotation(0)
    {
        _texture.loadFromFile("media/Player/Ship.png");
        _ship.setTexture(_texture);
        _ship.setOrigin(49.5,37.5);

        bind(PlayerInputs::Up,[this](const sf::Event&){
             _is_moving = true;
        });

        bind(PlayerInputs::Left,[this](const sf::Event&){
             _rotation-= 1;
         });

        bind(PlayerInputs::Right,[this](const sf::Event&){
             _rotation+= 1;
         });
    }
    
    void Player::processEvents()
    {
        _is_moving = false;
        _rotation = 0;
        ActionTarget::processEvents();
    }

    void Player::update(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();

        if(_rotation != 0)
        {
            float angle = _rotation*180*seconds;
            _ship.rotate(angle);
        }
        
        if(_is_moving)
        { 
            float angle = _ship.getRotation() / 180 * M_PI - M_PI / 2;
            _velocity += sf::Vector2f(std::cos(angle),std::sin(angle)) * 60.f * seconds;
        }

        _ship.move(seconds * _velocity);
    }

    void Player::setDefaultsInputs()
    {
        _player_inputs.map(PlayerInputs::Up,Action(sf::Keyboard::Up));
        _player_inputs.map(PlayerInputs::Right,Action(sf::Keyboard::Right));
        _player_inputs.map(PlayerInputs::Left,Action(sf::Keyboard::Left));
    }

   void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
       target.draw(_ship,states);
   }
}
