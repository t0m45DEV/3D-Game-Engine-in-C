#include "input.h"


keys_state_t action_keys_state =
{
    .move_forward  = 0,
    .move_backward = 0,
    .rotate_left   = 0,
    .rotate_right  = 0,
};


void buttons_down(unsigned char key, int x, int y)
{
    if (key == CHANGE_DEBUG_MODE)
    {
        debug_2D_view = !debug_2D_view;
    }
    else if (key == MOVE_FORWARD)
    {
        action_keys_state.move_forward = 1;
    }
    else if (key == MOVE_BACKWARD)
    {
        action_keys_state.move_backward = 1;
    }
    else if (key == ROTATE_LEFT)
    {
        action_keys_state.rotate_left = 1;
    }
    else if (key == ROTATE_RIGHT)
    {
        action_keys_state.rotate_right = 1;
    }
}

void buttons_up(unsigned char key, int x, int y)
{
    if (key == MOVE_FORWARD)
    {
        action_keys_state.move_forward = 0;
    }
    else if (key == MOVE_BACKWARD)
    {
        action_keys_state.move_backward = 0;
    }
    else if (key == ROTATE_LEFT)
    {
        action_keys_state.rotate_left = 0;
    }
    else if (key == ROTATE_RIGHT)
    {
        action_keys_state.rotate_right = 0;
    }
}


void move_player(void)
{
    if (action_keys_state.rotate_left)
    {
        player.angle -= ROTATE_VELOCITY * FPS_CORRECTION;
        player.angle = adjust_angle(player.angle);
        
        player.x_delta = CALCULATE_X_DELTA(player.angle) * player.velocity;
        player.y_delta = CALCULATE_Y_DELTA(player.angle) * player.velocity;
    }
    if (action_keys_state.rotate_right)
    {
        player.angle += ROTATE_VELOCITY * FPS_CORRECTION;
        player.angle = adjust_angle(player.angle);

        player.x_delta = CALCULATE_X_DELTA(player.angle) * player.velocity;
        player.y_delta = CALCULATE_Y_DELTA(player.angle) * player.velocity;
    }
    if (action_keys_state.move_forward)
    {
        if (!is_colliding_in_axis(player, FRONT_X_AXIS_COLLISION)) player.x_pos += player.x_delta * FPS_CORRECTION;
        if (!is_colliding_in_axis(player, FRONT_Y_AXIS_COLLISION))  player.y_pos += player.y_delta * FPS_CORRECTION;
    }
    if (action_keys_state.move_backward)
    {
        if (!is_colliding_in_axis(player, BACK_X_AXIS_COLLISION)) player.x_pos -= player.x_delta * FPS_CORRECTION;
        if (!is_colliding_in_axis(player, BACK_Y_AXIS_COLLISION))  player.y_pos -= player.y_delta * FPS_CORRECTION;
    }

    glutPostRedisplay();
}
