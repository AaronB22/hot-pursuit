class Player
{
public:
    Player(int starting_x, int starting_y, bn::fixed player_speed, bn::size player_size);

    /**
     * Update the position and bounding box of the player based on d-pad movement.
     */
    void update();
    bn::rect bounding_box();
    bn::sprite_ptr sprite();

private:
    // Create the sprite. This will be moved to a constructor
    bn::sprite_ptr _sprite;
    bn::fixed _speed;       // The speed of the player
    bn::size _size;         // The width and height of the sprite
    bn::rect _bounding_box; // The rectangle around the sprite for checking collision
};