#ifndef _H_PLAYER
#define _H_PLAYER

#include "entity.h"
#include "defines.h"

#define P_COLLISION_SIZE 20     /** Initial collision size for player (check MAP_CELL_SIZE for size relation) */

#define MOVEMENT_VELOCITY  100    /** Initial player movement velocity */
#define ROTATION_VELOCITY  2      /** Initial player rotation velocity */

#define P_INIT_ANGLE 0          /** Initial player vision angle (0 means bro is seeing right) */

/**
 * Returns the player current info in form of an entity
 */
entity_t get_player_info(void);

/**
 * Sets the player info to the current level 
 *
 * @note If you change or reset the level, call this function to update the player position, velocity, etc
 */
void reset_player_info(void);

/**
 * Move the player using the info in the player struct from player.h and the action_key_state struct from input.h
 */
void move_player(keys_state_t key_state, float delta_time);

/**
 * Draw the player in the screen in the actual player position.
 *
 * @note The player is represented as a yellow dot with a line in front of him. This line represent the face of the player.
 */
void draw_player(void);

/**
 * Check if is a door infront of the player. If that's true, opens the door
 */
void open_door(void);

#endif
