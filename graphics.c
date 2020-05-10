#include "graphics.h"

#define WINDOW_TITLE "Cardioid"

#define MIN(x, y) ((x) < (y) ? (x) : (y))

#ifdef CARDIOID_RELEASE
# define SDL_CALL(x) x
#else
# define SDL_CALL(x)                                  \
	SDL_ClearError();                                 \
	x;                                                \
	if (*SDL_GetError() != '\0') {                   \
		SDL_Log("[ERROR SDL] %s at %s:%d\n\t"#x,      \
				SDL_GetError(), __FILE__, __LINE__); \
		exit(EXIT_FAILURE);                           \
}
#endif

static void	update(t_state *state);
static void	event_handler(t_state *state);
static void	get_point(t_state *state, SDL_Point* dst, double index);
static void update_window_value(t_state *state, int width, int height);

void 		graphics_init(t_state *state, int width, int height)
{
	SDL_CALL(SDL_Init(SDL_INIT_VIDEO));
	SDL_CALL(state->window = SDL_CreateWindow(
				WINDOW_TITLE,
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				width,
				height,
				SDL_WINDOW_RESIZABLE
				));
	SDL_CALL(state->renderer = SDL_CreateRenderer(state->window, -1, 0));
	// looks less blocky, add color to draw with previous color.
	// The more lines are drawn to the same place the brighter it is.
	SDL_CALL(SDL_SetRenderDrawBlendMode(state->renderer, SDL_BLENDMODE_ADD));
	state->running    = true;
	state->points_num = POINTS_DEFAULT;
	state->factor     = FACTOR_DEFAULT;
	update_window_value(state, width, height);
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
		SDL_Delay(2);
	}
}

static void		update(t_state *state)
{
	SDL_Point	a;
	SDL_Point	b;

	SDL_CALL(SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255));
	SDL_CALL(SDL_RenderClear(state->renderer));

	SDL_CALL(SDL_SetRenderDrawColor(
		state->renderer,
		(LINE_COLOR >> 24) & 0xff,
		(LINE_COLOR >> 16) & 0xff,
		(LINE_COLOR >> 8 ) & 0xff,
		(LINE_COLOR >> 0 ) & 0xff
	));
	for (double i = 0.0; i < state->points_num; i += 1.0)
	{
		get_point(state, &a, i);
		get_point(state, &b, i * state->factor);
		SDL_CALL(SDL_RenderDrawLine(state->renderer, a.x, a.y, b.x, b.y));
	}

	SDL_CALL(SDL_RenderPresent(state->renderer));
}

static void		get_point(t_state *state, SDL_Point* dst, double index)
{
	double index_rem = fmod(index, state->points_num);
	double radian = M_PI_2 + 2.0 * M_PI * (index_rem / state->points_num);
	dst->x = cos(radian) * state->radius + state->center.x;
	dst->y = sin(radian) * state->radius + state->center.y;
}

static void		update_window_value(t_state *state, int width, int height)
{
	state->center.x   = width / 2.0;
	state->center.y   = height / 2.0;
	state->radius     = MIN(width, height) / 2.0 - 10.0;
}

static void		event_handler(t_state *state)
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
					case SDLK_j:
					case SDLK_DOWN:
						if (state->points_num < 3.0)
							state->points_num = 0.0;
						else
							state->points_num -= 3.0;
						break;
					case SDLK_k:
					case SDLK_UP:
						state->points_num += 3.0;
						break;
					case SDLK_u:
					case SDLK_LEFT:
						if (state->factor < 0.05)
							state->factor = 0.0;
						else
							state->factor -= 0.05;
						break;
					case SDLK_i:
					case SDLK_RIGHT:
						state->factor += 0.1;
						break;
				}
				break;

			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED)
					update_window_value(state, e.window.data1, e.window.data2);
		}
	}
}
