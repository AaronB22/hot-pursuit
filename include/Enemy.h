#ifndef ENEMY_H
#define ENEMY_H

#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>
#include <bn_rect.h>

#include "Player.h"
class Enemy
{
public:
    Enemy(int starting_x, int starting_y, bn::fixed enemy_speed, bn::size enemy_size);

    bool isTouching(Player &player);
    bn::sprite_ptr sprite();

    void update(Player &player);

private:
    // Create the sprite. This will be moved to a constructor
    bn::sprite_ptr _sprite;
    bn::fixed _speed;       // The speed of the player
    bn::size _size;         // The width and height of the sprite
    bn::rect _bounding_box; // The rectangle around the sprite for checking collision
};

#endif