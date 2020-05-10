#include "graphics.h"
#include "config.h"


int main()
{
	t_state		state;
	/* t_cardioid	cardioid; */

	/* if (cardioid_init(&cardioid, 10, WINDOW_WIDTH, WINDOW_HEIGHT) == -1) */
	/* { */
	/* 	fprintf(stderr, "[ERROR] couldn't initialize caridoid\n"); */
	/* 	return (1); */
	/* } */
	/* for (size_t i = 0; i < 10; i++) */
	/* { */
	/* 	printf("%d %d\n", cardioid.points[i].x, cardioid.points[i].y); */
	/* } */
	graphics_init(&state, WINDOW_WIDTH, WINDOW_HEIGHT);//, &cardioid);
	graphics_run(&state);
	graphics_quit(&state);
	/* cardioid_quit(&cardioid); */

	return 0;
}
