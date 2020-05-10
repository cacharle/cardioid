#include "graphics.h"

int main()
{
	t_state	state;

	graphics_init(&state, 640, 480);
	graphics_run(&state);
	graphics_quit(&state);

	return 0;
}
