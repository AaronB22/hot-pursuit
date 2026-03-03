#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_keypad.h>
#include <bn_display.h>

#include "bn_sprite_items_stop.h"

#include "Stop.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

bn::rect stop_create_bounding_box(bn::sprite_ptr sprite, bn::size box_size)
{
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

Stop::Stop(int starting_x, int starting_y,bn::size stop_size)
    : _sprite(bn::sprite_items::stop.create_sprite(starting_x, starting_y)),
      _size(stop_size),
      _bounding_box(stop_create_bounding_box(_sprite, _size))
{
}
/**
 * Update the position and bounding box of the player based on d-pad movement.
 */
// void Stop::update()
// {
   

//     _bounding_box = stop_create_bounding_box(_sprite, _size);
// }

// bn::rect Stop::bounding_box()
// {
//     return _bounding_box;
// }
bn::rect Stop::bounding_box()
{
    _bounding_box = stop_create_bounding_box(_sprite, _size);
    return _bounding_box;
}

bn::sprite_ptr Stop::sprite()
{
    return _sprite;
}