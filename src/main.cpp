#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_math.h>
#include <bn_random.h>

#include "common_fixed_8x16_font.h"
#include "bn_sprite_items_car.h"
#include "bn_sprite_items_cop.h"

#include "ScoreDisplay.h"
#include "Player.h"
#include "Enemy.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

// Limits of the game, aka the screen.
static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Max Amount of Enemies
static constexpr int MAXENEMIES = 10;

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
// Missing function

int main()
{
    bn::core::init();
    // Create Random Number Generator
    bn::random rng = bn::random();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    Player player = Player(48, 46, 2.4, PLAYER_SIZE);

    // bn::sprite_ptr enemy_sprite = bn::sprite_items::square.create_sprite(-30, 22);
    // bn::rect enemy_bounding_box = create_bounding_box(enemy_sprite, ENEMY_SIZE);
    Enemy starting_enemy = Enemy(-20, 30, 1.0, ENEMY_SIZE);
    bn::vector<Enemy, MAXENEMIES> enemies = {};
    enemies.push_back(starting_enemy);
    int framecounter = 0;

    while (true)
    {
        if (framecounter < 600)
        {
            framecounter++;
        }
        else
        {
            framecounter = 0;
        }
        player.update();

        // Reset the current score and player position if the player collides with enemy
        for (Enemy &enemy : enemies)
        {
            enemy.update(player);
            if (enemy.isTouching(player))
            {
                scoreDisplay.resetScore();
                // Reset player position
                player.sprite().set_x(44);
                player.sprite().set_y(22);
                // Set random enemy position
                enemy.sprite().set_x(rng.get_int(MIN_X, MAX_X));
                enemy.sprite().set_y(rng.get_int(MIN_Y, MAX_Y));
            }
        }
        if (enemies.size() < MAXENEMIES)
        {
            if (framecounter % 100 == 0)
            {
                Enemy new_enemy = Enemy(-20, 30, 1.0, ENEMY_SIZE);
                enemies.push_back(new_enemy);
            }
        }
        // Update random number generator
        rng.update();

        // Update the scores and disaply them
        scoreDisplay.update();

        bn::core::update();
    }
}