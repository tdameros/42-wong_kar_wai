#ifndef GRID_H
# define GRID_H

# include "engine.h"

#include <ncurses.h>
# include <stdint.h>

typedef enum e_move {
    RIGHT,
    LEFT,
    UP,
    DOWN,
}   t_move; 

void set_tile_coord(t_engine *engine , uint32_t x, uint32_t y, uint32_t value);
uint32_t get_tile_coord(t_engine *engine, uint32_t x, uint32_t y);
void set_tile_index(t_engine *engine, uint32_t index, uint32_t value);
uint32_t get_tile_index(t_engine *engine, uint32_t index);
uint32_t convert_coord_to_index(t_engine *engine, uint32_t x, uint32_t y);

int8_t place_random_tile(t_engine *engine);
int8_t play_move(t_engine *engine, t_move move);

#endif