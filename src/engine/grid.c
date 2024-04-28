#include <stdlib.h>

#include "engine.h"

static uint8_t generate_new_random_tile_value(void);
static uint8_t generate_new_random_position(t_engine *engine);

void set_tile_coord(t_engine *engine, uint32_t x, uint32_t y, uint32_t value) {
  engine->grid[engine->grid_size * y + x] = value;
}

int32_t get_tile_coord(t_engine *engine, uint32_t x, uint32_t y) {
  return engine->grid[engine->grid_size * y + x];
}

void set_tile_index(t_engine *engine, uint32_t index, uint32_t value) {
  engine->grid[index] = value;
}

int32_t get_tile_index(t_engine *engine, uint32_t index) {
  return engine->grid[index];
}

int32_t convert_coord_to_index(t_engine *engine, uint32_t x, uint32_t y) {
  return engine->grid_size * y + x;
}

int8_t place_random_tile(t_engine *engine) {
  uint32_t tile_value = generate_new_random_tile_value();
  uint32_t rand_x = generate_new_random_position(engine);
  uint32_t rand_y = generate_new_random_position(engine);

  for (int32_t i = convert_coord_to_index(engine, rand_x, rand_y);
       i < engine->grid_size * engine->grid_size; i++) {
    if (get_tile_index(engine, i) == 0) {
      set_tile_index(engine, i, tile_value);
      return 0;
    }
  }
  for (int32_t i = 0; i < convert_coord_to_index(engine, rand_x, rand_y); i++) {
    if (get_tile_index(engine, i) == 0) {
      set_tile_index(engine, i, tile_value);
      return 0;
    }
  }
  return -1;
}

static uint8_t generate_new_random_tile_value(void) {
  return (rand() % 10 == 1 ? NEW_TILE * 2 : NEW_TILE);
}

static uint8_t generate_new_random_position(t_engine *engine) {
  return (rand() % engine->grid_size);
}
