#include <ncurses.h>
#include <locale.h>

#include "grid.h"
#include "display.h"

static void print_template(uint32_t x_start, uint32_t y_start, uint32_t size, uint32_t grid_size);
static void print_number(uint32_t x, uint32_t y, uint32_t tile_size, uint32_t value);
static void fill_tile(uint32_t start_x, uint32_t start_y, uint32_t tile_size);
static void print_ascii_nbr(uint32_t x, uint32_t y, uint32_t value);
static uint32_t get_ascii_len(uint32_t value);

static void print_0_ascii(uint32_t x, uint32_t y);
static void print_1_ascii(uint32_t x, uint32_t y);
static void print_2_ascii(uint32_t x, uint32_t y);
static void print_3_ascii(uint32_t x, uint32_t y);
static void print_4_ascii(uint32_t x, uint32_t y);
static void print_5_ascii(uint32_t x, uint32_t y);
static void print_6_ascii(uint32_t x, uint32_t y);
static void print_7_ascii(uint32_t x, uint32_t y);
static void print_8_ascii(uint32_t x, uint32_t y);
static void print_9_ascii(uint32_t x, uint32_t y);

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
        attron(COLOR_PAIR(get_color_id(value)));
        fill_tile((x_start + x * (size * 2 / engine->grid_size)) , (y_start + y * size / engine->grid_size), size / engine->grid_size);
        dprintf(2, "size ascii of %d = %d\n", value, get_ascii_len(value));
        if (value == 0 || get_ascii_len(value) > size * 2 / engine->grid_size || get_ascii_len(value) > 6)
          print_number((x_start + x * (size * 2 / engine->grid_size)) , (y_start + y * size / engine->grid_size), size / engine->grid_size, value);
        else
          print_ascii_nbr((x_start + x * (size * 2 / engine->grid_size)), (y_start + y * size / engine->grid_size), value);
        attroff(COLOR_PAIR(get_color_id(value)));
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
  if (value > 0){
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
}

static void fill_tile(uint32_t start_x, uint32_t start_y, uint32_t tile_size)
{
  for (uint32_t x = start_x + 1; x < start_x + tile_size * 2; x++)
  {
    for (uint32_t y = start_y + 1; y < start_y + tile_size; y++)
    {
      mvprintw(y, x, " ");
    }
  }
}

static uint32_t get_ascii_len(uint32_t value) {
  uint32_t size = 0;
  while (value >= 0)
  {
    uint32_t digit = value % 10;
    if (digit == 0)
      size += ASCII_0;
    else if (digit == 1)
      size += ASCII_1;
    else if (digit == 2)
      size += ASCII_2;
    else if (digit == 3)
      size += ASCII_3;
    else if (digit == 4)
      size += ASCII_4;
    else if (digit == 5)
      size += ASCII_5;
    else if (digit == 6)
      size += ASCII_6;
    else if (digit == 7)
      size += ASCII_7;
    else if (digit == 8)
      size += ASCII_8;
    else if (digit == 9)
      size += ASCII_9;
    value /= 10;
  }
  return size;
}

static void print_ascii_nbr(uint32_t x, uint32_t y, uint32_t value)
{
  uint32_t digit;
  if (value > 9)
  {
    digit = value % 10;
    if (digit == 0)
      print_ascii_nbr(x += ASCII_0, y, value / 10);
    else if (digit == 1)
      print_ascii_nbr(x += ASCII_1, y, value / 10);
    else if (digit == 2)
      print_ascii_nbr(x += ASCII_2, y, value / 10);
    else if (digit == 3)
      print_ascii_nbr(x += ASCII_3, y, value / 10);
    else if (digit == 4)
      print_ascii_nbr(x += ASCII_4, y, value / 10);
    else if (digit == 5)
      print_ascii_nbr(x += ASCII_5, y, value / 10);
    else if (digit == 6)
      print_ascii_nbr(x += ASCII_6, y, value / 10);
    else if (digit == 7)
      print_ascii_nbr(x += ASCII_7, y, value / 10);
    else if (digit == 8)
      print_ascii_nbr(x += ASCII_8, y, value / 10);
    else if (digit == 9)
      print_ascii_nbr(x += ASCII_9, y, value / 10);
  }
  digit = value % 10;
  if (digit == 0)
    print_0_ascii(x, y);
  else if (digit == 1)
    print_1_ascii(x, y);
  else if (digit == 2)
    print_2_ascii(x, y);
  else if (digit == 3)
    print_3_ascii(x, y);
  else if (digit == 4)
    print_4_ascii(x, y);
  else if (digit == 5)
    print_5_ascii(x, y);
  else if (digit == 6)
    print_6_ascii(x, y);
  else if (digit == 7)
    print_7_ascii(x, y);
  else if (digit == 8)
    print_8_ascii(x, y);
  else if (digit == 9)
    print_9_ascii(x, y);
}


static void print_0_ascii(uint32_t x, uint32_t y)
{
    mvprintw(y + 0, x, " ██████╗ ");
    mvprintw(y + 1, x, "██╔═████╗");
    mvprintw(y + 2, x, "██║██╔██║");
    mvprintw(y + 3, x, "████╔╝██║");
    mvprintw(y + 4, x, "╚██████╔╝");
    mvprintw(y + 5, x, " ╚═════╝ ");
}

static void print_1_ascii(uint32_t x, uint32_t y)
{
    mvprintw(y + 0, x, " ██╗");
    mvprintw(y + 1, x, "███║");
    mvprintw(y + 2, x, "╚██║");
    mvprintw(y + 3, x, " ██║");
    mvprintw(y + 4, x, " ██║");
    mvprintw(y + 5, x, " ╚═╝");
}

static void print_2_ascii(uint32_t x, uint32_t y)
{
    mvprintw(y + 0, x, "██████╗ ");
    mvprintw(y + 1, x, "╚════██╗");
    mvprintw(y + 2, x, " █████╔╝");
    mvprintw(y + 3, x, "██╔═══╝ ");
    mvprintw(y + 4, x, "███████╗");
    mvprintw(y + 5, x, "╚══════╝");
}

static void print_3_ascii(uint32_t x, uint32_t y)
{
    mvprintw(y + 0, x, "██████╗ ");
    mvprintw(y + 1, x, "╚════██╗");
    mvprintw(y + 2, x, " █████╔╝");
    mvprintw(y + 3, x, " ╚═══██╗");
    mvprintw(y + 4, x, "██████╔╝");
    mvprintw(y + 5, x, "╚═════╝ ");
}

static void print_4_ascii(uint32_t x, uint32_t y)
{
    mvprintw(y + 0, x, "██╗  ██╗");
    mvprintw(y + 1, x, "██║  ██║");
    mvprintw(y + 2, x, "███████║");
    mvprintw(y + 3, x, "╚════██║");
    mvprintw(y + 4, x, "     ██║");
    mvprintw(y + 5, x, "     ╚═╝");
}

static void print_5_ascii(uint32_t x, uint32_t y)
{
    mvprintw(y + 0, x, "███████╗");
    mvprintw(y + 1, x, "██╔════╝");
    mvprintw(y + 2, x, "███████╗");
    mvprintw(y + 3, x, "╚════██║");
    mvprintw(y + 4, x, "███████║");
    mvprintw(y + 5, x, "╚══════╝");
}

static void print_6_ascii(uint32_t x, uint32_t y)
{
    mvprintw(y + 0, x, " ██████╗ ");
    mvprintw(y + 1, x, "██╔════╝ ");
    mvprintw(y + 2, x, "███████╗ ");
    mvprintw(y + 3, x, "██╔═══██╗");
    mvprintw(y + 4, x, "╚██████╔╝");
    mvprintw(y + 5, x, " ╚═════╝ ");
}

static void print_7_ascii(uint32_t x, uint32_t y)
{
    mvprintw(y + 0, x, "███████╗");
    mvprintw(y + 1, x, "╚════██║");
    mvprintw(y + 2, x, "    ██╔╝");
    mvprintw(y + 3, x, "   ██╔╝ ");
    mvprintw(y + 4, x, "   ██║  ");
    mvprintw(y + 5, x, "   ╚═╝  ");
}

static void print_8_ascii(uint32_t x, uint32_t y)
{
    mvprintw(y + 0, x, " █████╗ ");
    mvprintw(y + 1, x, "██╔══██╗");
    mvprintw(y + 2, x, "╚█████╔╝");
    mvprintw(y + 3, x, "██╔══██╗");
    mvprintw(y + 4, x, "╚█████╔╝");
    mvprintw(y + 5, x, " ╚════╝ ");
}

static void print_9_ascii(uint32_t x, uint32_t y)
{
    mvprintw(y + 0, x, " █████╗ ");
    mvprintw(y + 1, x, "██╔══██╗");
    mvprintw(y + 2, x, "╚██████║");
    mvprintw(y + 3, x, " ╚═══██║");
    mvprintw(y + 4, x, " █████╔╝");
    mvprintw(y + 5, x, " ╚════╝ ");
}