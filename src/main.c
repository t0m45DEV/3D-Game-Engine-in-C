#include <stdio.h>
#include <stdbool.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <GL/gl.h>

#include "defines.h"
#include "loop.h"

game_state_t game_state = {0};

bool init_GL(void)
{
    // Initialize projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Check for errors
    if (glGetError() != GL_NO_ERROR)
    {
        printf("Error initializing OpenGL projection matrix!\n");
        return false;
    }
    glOrtho(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0, -1.0, 1.0);
    
    // Initialize modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Check for errors
    if (glGetError() != GL_NO_ERROR)
    {
        printf("Error initializing OpenGL modelview matrix!\n");
        return false;
    }
    return true;
}

int main(void)
{
    game_state.is_game_running = true;

    load_level(FIRST_LEVEL);

    /* Try to initialize SDL */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    /* To use OpenGL legacy functions */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    window = create_window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    if (!init_GL())
    {
        printf("Unable to initialize OpenGL\n");
        exit(EXIT_FAILURE);
    }
    set_background_color(BACKGROUND_COLOR);

    //engine_timer_t animation_timer = create_timer(0.3);
    //start_timer(&animation_timer);

    engine_timer_t fps_timer = create_timer(1);
    FPS_counter.timer = &fps_timer;
    start_timer(&fps_timer);

    // The division is to the get the time in seconds, not in miliseconds
    float actual_frame = SDL_GetTicks() / SECONDS_TO_MILLISECONDS(1);
    FPS_counter.actual_frame = actual_frame;

    while (game_state.is_game_running)
    {
        main_loop();
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    exit(EXIT_SUCCESS);
}
