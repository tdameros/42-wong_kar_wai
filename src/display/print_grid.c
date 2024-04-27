#include <ncurses.h>
#include <locale.h>

#include "grid.h"
#include "display.h"

static void print_template(uint32_t x_start, uint32_t y_start, uint32_t size, uint32_t grid_size);
static void print_number(uint32_t x, uint32_t y, uint32_t tile_size, uint32_t value);

void print_grid(t_engine *engine) {
  uint32_t width;
  uint32_t height;
  uint32_t size;

	clear();
  getmaxyx(stdscr, height, width);

  size = width / 2 > height ? height - GRID_MARGIN * 2: width / 2 - GRID_MARGIN * 2;
  size -= size % engine->grid_size;
  uint32_t x_start = (width - size * 2) / 2;
  uint32_t y_start = (height - size) / 2;
  if (size > 10)
 	  print_template(x_start, y_start, size, engine->grid_size);

	move(0, 0);
  printw("width = %d, height = %d, size = %d\n", width, height, size);
  for (int32_t y = 0; y < engine->grid_size; y++)
  {
    for (int32_t x = 0; x < engine->grid_size; x++) {
      uint32_t value = get_tile_coord(engine, x, y);
      if (value > 0)
        print_number((x_start + x * (size * 2 / engine->grid_size)) , (y_start + y * size / engine->grid_size), size / engine->grid_size, value);
    }
  }
  refresh();
}

static void print_template(uint32_t x_start, uint32_t y_start, uint32_t size, uint32_t grid_size)
{
	for (uint32_t x = x_start; x < size * 2 + x_start + 1; x +=  (size * 2) / grid_size) {
		for (uint32_t y = y_start; y < size + y_start + 1; y++) {
          mvprintw(y, x, "│");
		}
	}
  for (uint32_t y = y_start; y < size + y_start + 1; y += size / grid_size) {
    for (uint32_t x = x_start; x < size * 2 + x_start + 1; x++) {
  		if (y == y_start && x == x_start)
			mvprintw(y, x, "┌");
		else if (y == y_start && x == size * 2 + x_start)
			mvprintw(y, x, "┐");
		else if (y == size + y_start && x == x_start)
			mvprintw(y, x, "└");
		else if (y == size + y_start && x == size * 2 + x_start)
			mvprintw(y, x, "┘");
    else if (x == x_start)
        mvprintw(y, x, "├");
    else if (x == size * 2 + x_start)
        mvprintw(y, x, "┤");
    else if (y == y_start && x % (size * 2 / grid_size) == x_start % (size * 2 / grid_size))
        mvprintw(y, x, "┬");
    else if (y == size + y_start && x % (size * 2 / grid_size) == x_start % (size * 2 / grid_size))
        mvprintw(y, x, "┴");
    else if (x % (size * 2 / grid_size) == x_start % (size * 2 / grid_size))
        mvprintw(y, x, "┼");
		else
			mvprintw(y, x, "─");
    }
  }
}

static void print_number(uint32_t x, uint32_t y, uint32_t tile_size, uint32_t value)
{
  uint32_t value_size = 1;
  uint32_t value_tmp = value;
  while (value_tmp > 9)
  {
    value_tmp /= 10;
    value_size++;
  }
  uint32_t x_offset = x + (tile_size * 2 - value_size) / 2 + 1;
  uint32_t y_offset = y + tile_size / 2 ;
  mvprintw(y_offset, x_offset, "%d", value);
}
