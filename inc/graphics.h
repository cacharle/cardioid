#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <stdbool.h>
# include <SDL2/SDL.h>

typedef struct
{
    SDL_Window		*window;
    SDL_Renderer	*renderer;
    bool 			running;
}					t_state;

void graphics_init(t_state *state, int width, int height);
void graphics_quit(t_state *state);
void graphics_run(t_state *state);

#endif
