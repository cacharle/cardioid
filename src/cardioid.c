#include "cardioid.h"

int		cardioid_init(t_cardioid *cardioid, size_t points_num, int width, int height)
{
	cardioid->points = NULL;
	cardioid->points_num = points_num;
	return (cardioid_update_window(cardioid, width, height));
}

int		cardioid_update_window(t_cardioid *cardioid, int width, int height)
{
	cardioid->center.x = width / 2;
	cardioid->center.y = height / 2;
	cardioid->radius = MIN(width, height) / 2 - 10;
	printf("%d %d, %lu\n", cardioid->center.x,
                        cardioid->center.y,
                        cardioid->radius);

	return (cardioid_update_points(cardioid, cardioid->points_num));
}

int		cardioid_update_points(t_cardioid *cardioid, size_t points_num)
{
	double		radian_step;
	double		radian_pos;

	cardioid->points = realloc(cardioid->points, sizeof(SDL_Point) * points_num);
	if (cardioid->points == NULL)
		return (-1);
	cardioid->points_num = points_num;
	radian_pos = 0;
	radian_step = (2 * M_PI) / points_num;
	for (size_t i = 0; i < points_num; i++)
	{
		cardioid->points[i].x = cos(radian_pos) * (double)cardioid->radius + (double)cardioid->center.x;
		cardioid->points[i].y = sin(radian_pos) * (double)cardioid->radius + (double)cardioid->center.y;
		radian_pos += radian_step;
	}
	return (0);
}

void	cardioid_quit(t_cardioid *cardioid)
{
	free(cardioid->points);
}
