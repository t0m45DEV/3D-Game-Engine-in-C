#include "input.h"

keys_state_t action_keys_state = {0};

bool handle_input(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) // If the window closes
    {
        return false;
    }
    // Simultaneous input
    SDL_PumpEvents();
    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

    action_keys_state.move_forward = (keyboard_state[MOVE_FORWARD_BUTTON] != 0);
    action_keys_state.move_backward = (keyboard_state[MOVE_BACKWARD_BUTTON] != 0);
    action_keys_state.rotate_anti_clockwise = (keyboard_state[ROTATE_ANTI_CLOCKWISE_BUTTON] != 0);
    action_keys_state.rotate_clockwise = (keyboard_state[ROTATE_CLOCKWISE_BUTTON] != 0);

    // Simple input
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        if (get_scancode(event) == CHANGE_DEBUG_MODE_BUTTON)
        {
            debug_2D_view = !debug_2D_view;

            //if (resolution == HIGH_RESOLUTION) resolution = LOW_RESOLUTION;
            //else
            //resolution = HIGH_RESOLUTION;

            //if (current_level == 0) change_to_level(1);
            //else change_to_level(0);
        }
        if (get_scancode(event) == OPEN_DOOR_BUTTON)
        {
            open_door();
        }
    }
    return true;
}

SDL_Scancode get_scancode(const SDL_Event event)
{
    return event.key.keysym.scancode;
}
