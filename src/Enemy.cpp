#include <bn_fixed.h>
#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_sprite_items_cop.h>
#include <bn_math.h>

#include "Player.h"
#include "Enemy.h"

bn::rect enemy_create_bounding_box(bn::sprite_ptr sprite, bn::size box_size)
{
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

Enemy::Enemy(int starting_x, int starting_y, bn::fixed enemy_speed, bn::size enemy_size)
    : _sprite(bn::sprite_items::cop.create_sprite(starting_x, starting_y)),
      _speed(enemy_speed),
      _size(enemy_size),
      _bounding_box(enemy_create_bounding_box(_sprite, _size))
{
}

bool Enemy::isTouching(Player &player)
{
    return _bounding_box.intersects(player.bounding_box());
}

bn::sprite_ptr Enemy::sprite()
{
    return _sprite;
}

void Enemy::update(Player &player)
{
    bn::fixed player_x = player.sprite().x();
    bn::fixed player_y = player.sprite().y();
    bn::fixed enemy_x = _sprite.x();
    bn::fixed enemy_y = _sprite.y();
    // Get direction to player from enemy
    bn::fixed vectX = player_x - enemy_x;
    bn::fixed vectY = player_y - enemy_y;
    // Turn that direction into a "unit" vector. (magnitude of 1)
    bn::fixed magnitude = bn::sqrt((vectX * vectX) + (vectY * vectY));
    vectX /= magnitude;
    vectY /= magnitude;
    // Move the enemy along that vector at a magnitude of speed.
    _sprite.set_x(enemy_x + vectX * _speed);
    _sprite.set_y(enemy_y + vectY * _speed);
    _bounding_box = enemy_create_bounding_box(_sprite, _size);
}