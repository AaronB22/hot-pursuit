#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_sprite_items_dot.h>
#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_keypad.h>
#include <bn_display.h>

#include "Player.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

bn::rect player_create_bounding_box(bn::sprite_ptr sprite, bn::size box_size)
{
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

Player::Player(int starting_x, int starting_y, bn::fixed player_speed, bn::size player_size)
    : _sprite(bn::sprite_items::dot.create_sprite(starting_x, starting_y)),
      _speed(player_speed),
      _size(player_size),
      _bounding_box(player_create_bounding_box(_sprite, _size))
{
}
/**
 * Update the position and bounding box of the player based on d-pad movement.
 */
void Player::update()
{
    if (bn::keypad::right_held())
    {
        _sprite.set_x(_sprite.x() + _speed);
    }
    if (bn::keypad::left_held())
    {
        _sprite.set_x(_sprite.x() - _speed);
    }
    if (bn::keypad::up_held())
    {
        _sprite.set_y(_sprite.y() - _speed);
    }
    if (bn::keypad::down_held())
    {
        _sprite.set_y(_sprite.y() + _speed);
    }
    // Screen Limits
    if (_sprite.x() > MAX_X)
    {
        _sprite.set_x(MAX_X);
    }
    if (_sprite.x() < MIN_X)
    {
        _sprite.set_x(MIN_X);
    }
    if (_sprite.y() > MAX_Y)
    {
        _sprite.set_y(MAX_Y);
    }
    if (_sprite.y() < MIN_Y)
    {
        _sprite.set_y(MIN_Y);
    }

    _bounding_box = player_create_bounding_box(_sprite, _size);
}

bn::rect Player::bounding_box()
{
    return _bounding_box;
}

bn::sprite_ptr Player::sprite()
{
    return _sprite;
}