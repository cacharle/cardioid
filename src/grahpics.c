#include "graphics.h"

#define WINDOW_TITLE "Title"

static const char	*g_sdl_error_str;

#define	SDL_CALL(x)                              \
	SDL_ClearError();                            \
	x;                                           \
	g_sdl_error_str = SDL_GetError();            \
	if (*g_sdl_error_str != '\0') {              \
    	SDL_Log("ERROR SDL: %s", g_sdl_error_str); \
		exit(EXIT_FAILURE);                      \
	}


static void	update(t_state *state);
static void	event_handler(t_state *state);

void		graphics_init(t_state *state, int width, int height)
{
    SDL_CALL(SDL_Init(SDL_INIT_VIDEO));
    SDL_CALL(state->window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		0
	));
    SDL_CALL(state->renderer = SDL_CreateRenderer(state->window, -1, 0));
    state->running = true;
}

void 		graphics_quit(t_state *state)
{
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    SDL_Quit();
}

void 		graphics_run(t_state *state)
{
    while (state->running)
    {
        event_handler(state);
        update(state);
        SDL_Delay(3);
    }
}

static
void		update(t_state *state)
{
    // do stuff
}

static
void		event_handler(t_state *state)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                state->running = false;
                break;
        }
    }
}
