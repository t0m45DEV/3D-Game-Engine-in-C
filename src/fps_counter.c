#include "fps_counter.h"

/**
 * A little self-explanatory
 * 
 * @param actual_frame Is the current time (in ticks)
 * @param last_frame   Is the last saved time (in ticks)
 * @param fps          Current count of frames
 * @param timer        A timer of 1 second, after that it should resets back
 */
typedef struct {
    float actual_frame;
    float last_frame;
    int fps;
    engine_timer_t timer;
} FPS_counter_t;

FPS_counter_t FPS_counter = {0}; /** The struct that tracks current FPS */

void init_fps_counter(void)
{
    FPS_counter.timer = create_timer(1);
    start_timer(&FPS_counter.timer);

    // The division is to the get the time in seconds, not in miliseconds
    FPS_counter.actual_frame = SDL_GetTicks() / SECONDS_TO_MILLISECONDS(1);
}

void update_fps_counter(void)
{
    FPS_counter.last_frame = FPS_counter.actual_frame;
    FPS_counter.actual_frame = SDL_GetTicks() / SECONDS_TO_MILLISECONDS(1);

    FPS_counter.fps++;

    if (is_timer_up(&FPS_counter.timer))
    {
        game_state.fps = FPS_counter.fps;
        FPS_counter.fps = 0;
        start_timer(&FPS_counter.timer);
    }
}
