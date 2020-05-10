#include "graphics.h"

#define WINDOW_TITLE "Cardioid"

static const char	*g_sdl_error_str;

#ifdef CARDIOID_RELEASE
# define SDL_CALL(x) x
#else
# define SDL_CALL(x)                                  \
	SDL_ClearError();                                 \
	x;                                                \
	g_sdl_error_str = SDL_GetError();                 \
	if (*g_sdl_error_str != '\0') {                   \
		SDL_Log("[ERROR SDL] %s at %s:%d\n\t"#x,      \
				g_sdl_error_str, __FILE__, __LINE__); \
		exit(EXIT_FAILURE);                           \
}
#endif


static void	update(t_state *state);
static void	event_handler(t_state *state);
static void	draw_lines(t_state *state);

void 		graphics_init(t_state *state, int width, int height, t_cardioid *cardioid)
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
	state->cardioid = cardioid;
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
	SDL_CALL(SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255));
	SDL_CALL(SDL_RenderClear(state->renderer));
	SDL_CALL(SDL_SetRenderDrawColor(state->renderer, 200, 150, 150, 255));
	SDL_CALL(SDL_RenderDrawPoints(state->renderer, state->cardioid->points, state->cardioid->points_num));
	draw_lines(state);
	SDL_CALL(SDL_RenderPresent(state->renderer));
}

	static
void		draw_lines(t_state *state)
{
	SDL_Point *points = state->cardioid->points;
	SDL_Point *paired;

	for (size_t i = 0; i < state->cardioid->points_num; i++)
	{
		paired = &points[i * 10 % state->cardioid->points_num];
		SDL_CALL(SDL_RenderDrawLine(state->renderer, points[i].x, points[i].y, paired->x, paired->y));
	}
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
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
					case SDLK_j: CARDIOID_SUB_POINTS(state->cardioid, 3); break;
					case SDLK_k: CARDIOID_ADD_POINTS(state->cardioid, 3); break;
				}
				break;
		}
	}
}
