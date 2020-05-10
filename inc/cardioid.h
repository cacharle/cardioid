#ifndef CARDIOID_H
# define CARDIOID_H

# include <stddef.h>
# include <SDL2/SDL.h>

typedef struct
{
	size_t		points_num;
	SDL_Point	*points;
	SDL_Point	center;
	size_t		radius;
	// double		multiplication;
}				t_cardioid;

# define MIN(x, y) ((x) < (y) ? (x) : (y))

# define CARDIOID_ADD_POINTS(cardioid, n) cardioid_update_points((cardioid), (cardioid)->points_num + (n))
# define CARDIOID_SUB_POINTS(cardioid, n) \
	cardioid_update_points((cardioid), (cardioid)->points_num < (n) ? 0 : (cardioid)->points_num - (n))

int				cardioid_init(t_cardioid *cardioid, size_t points_num, int width, int height);
int				cardioid_update_window(t_cardioid *cardioid, int width, int height);
int				cardioid_update_points(t_cardioid *cardioid, size_t points_num);
void			cardioid_quit(t_cardioid *cardioid);

#endif
