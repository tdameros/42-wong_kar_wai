#include "grid.h"
#include <ncurses.h>

void print_grid(t_engine *engine)
{
	// int	width;
	// int height;

	// getmaxyx(stdscr, width, height);
	// move(0, 0);
	for (int32_t y = 0; y < engine->grid_size; y++)
	{
		printf("---------------------\n");
		printf("|    |    |    |    |\n");
		printf("|%4d|%4d|%4d|%4d|\n", get_tile_coord(engine, 0, y), get_tile_coord(engine, 1, y), get_tile_coord(engine, 2, y), get_tile_coord(engine, 3, y));
		printf("|    |    |    |    |\n");
	}
	printf("---------------------\n");
}