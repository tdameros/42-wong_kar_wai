#include "engine.h"
#include "grid.h"

static void play_all_move(t_engine *engine, int32_t start, int8_t way,
                          t_move move);
static void join_all_move(t_engine *engine, int32_t start, int8_t way,
                          t_move move);

void play_move(t_engine *engine, t_move move) {
  switch (move) {
    case RIGHT:
      play_all_move(engine, engine->grid_size - 1, -1, move);
      join_all_move(engine, engine->grid_size - 1, -1, move);
      play_all_move(engine, engine->grid_size - 1, -1, move);
      break;
    case LEFT:
      play_all_move(engine, 0, 1, move);
      join_all_move(engine, 0, 1, move);
      play_all_move(engine, 0, 1, move);
    case UP:
      play_all_move(engine, 0, 1, move);
      join_all_move(engine, 0, 1, move);
      play_all_move(engine, 0, 1, move);
      break;
    case DOWN:
      play_all_move(engine, engine->grid_size - 1, -1, move);
      join_all_move(engine, engine->grid_size - 1, -1, move);
      play_all_move(engine, engine->grid_size - 1, -1, move);
    default:
      break;
  }
}

static void play_all_move(t_engine *engine, int32_t start, int8_t way,
                          t_move move) {
  for (int32_t y = 0; y < engine->grid_size; y++) {
    for (int32_t i = 0; i < engine->grid_size; i++) {
      int32_t x = start - i * -way;
      int32_t offset = 0;
      for (int32_t k = 0; k < i; k++) {
        if (move == RIGHT || move == LEFT)
          offset += get_tile_coord(engine, start - k * -way, y) == 0;
        else
          offset += get_tile_coord(engine, y, start - k * -way) == 0;
      }
      if (move == RIGHT || move == LEFT) {
        uint32_t value = get_tile_coord(engine, x, y);
        set_tile_coord(engine, x, y, 0);
        set_tile_coord(engine, x + offset * -way, y, value);
      } else {
        uint32_t value = get_tile_coord(engine, y, x);
        set_tile_coord(engine, y, x, 0);
        set_tile_coord(engine, y, x + offset * -way, value);
      }
    }
  }
}

static void join_all_move(t_engine *engine, int32_t start, int8_t way,
                          t_move move) {
  for (int32_t y = 0; y < engine->grid_size; y++) {
    for (int32_t i = 0; i < engine->grid_size - 1; i++) {
      int32_t x = start - i * -way;
      if (move == RIGHT || move == LEFT) {
        uint32_t value = get_tile_coord(engine, x, y);
        uint32_t next_value = get_tile_coord(engine, x + way, y);
        if (value == next_value) {
          set_tile_coord(engine, x, y, value * 2);
          set_tile_coord(engine, x + way, y, 0);
        }
      } else {
        uint32_t value = get_tile_coord(engine, y, x);
        uint32_t next_value = get_tile_coord(engine, y, x + way);
        if (value == next_value) {
          set_tile_coord(engine, y, x, value * 2);
          set_tile_coord(engine, y, x + way, 0);
        }
      }
    }
  }
}
