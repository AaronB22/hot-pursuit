#ifndef STOP_H
#define STOP_H

#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>
#include <bn_rect.h>

class Stop
{
public:

    Stop(int starting_x, int starting_y, bn::size stop_size);

    bn::rect bounding_box();
    bn::sprite_ptr sprite();

    void update(Stop &stop);

private:
    // Create the sprite. This will be moved to a constructor
    bn::sprite_ptr _sprite;
    bn::size _size;         // The width and height of the sprite
    bn::rect _bounding_box; // The rectangle around the sprite for checking collision
};

#endif