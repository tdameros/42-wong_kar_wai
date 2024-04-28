#include "engine.h"
#include "grid.h"

#include <stddef.h>

static uint8_t play_horizontaly_move(t_engine *engine, int32_t start, int32_t way);
static uint8_t play_verticaly_move(t_engine *engine, int32_t start, int32_t way);
static uint8_t join_horizontaly_move(t_engine *engine, int32_t start, int32_t way);
static uint8_t join_verticaly_move(t_engine *engine, int32_t start, int32_t way);
static bool can_join_horizontaly(t_engine *engine, int32_t start, int32_t way);
static bool can_join_verticaly(t_engine *engine, int32_t start, int32_t way);
static uint8_t move_right(t_engine *engine);
static uint8_t move_left(t_engine *engine);
static uint8_t move_up(t_engine *engine);
static uint8_t move_down(t_engine *engine);

int8_t play_move(t_engine *engine, t_move move) {
  switch (move) {
    case RIGHT:
      return (move_right(engine));
    case LEFT:
      return (move_left(engine));
    case UP:
      return (move_up(engine));
    case DOWN:
      return (move_down(engine));
    default:
      return (1);
  }
}

bool can_play(t_engine *engine) {
  for (int32_t y = 0; y < engine->grid_size; y++) {
    for (int32_t x = 0; x < engine->grid_size; x++) {
      if (get_tile_coord(engine, x, y) == 0) {
        return true;
      }
    }
  }
  return (can_join_horizontaly(engine, 0, 1) || can_join_horizontaly(engine, engine->grid_size - 1, -1)
        || can_join_verticaly(engine, 0, 1) || can_join_verticaly(engine, engine->grid_size - 1, -1));

}

bool is_win(t_engine *engine) {
  for (int32_t y = 0; y < engine->grid_size; y++) {
    for (int32_t x = 0; x < engine->grid_size; x++) {
      if (get_tile_coord(engine, x, y) == WIN_VALUE) {
        return true;
      }
    }
  }
  return false;
}

static uint8_t move_left(t_engine *engine){
  uint8_t result = 0;
  result += play_horizontaly_move(engine, 0, 1);
  result += join_horizontaly_move(engine, 0, 1);
  result += play_horizontaly_move(engine, 0, 1);
  return (result);
}

static uint8_t move_right(t_engine *engine){
  uint8_t result = 0;
  result += play_horizontaly_move(engine, engine->grid_size - 1, -1);
  result += join_horizontaly_move(engine, engine->grid_size - 1, -1);
  result += play_horizontaly_move(engine, engine->grid_size - 1, -1);
  return (result);
}

static uint8_t move_up(t_engine *engine){
  uint8_t result = 0;
  result += play_verticaly_move(engine, 0, 1);
  result += join_verticaly_move(engine, 0, 1);
  result += play_verticaly_move(engine, 0, 1);
  return (result);
}

static uint8_t move_down(t_engine *engine){
  uint8_t result = 0;
  result += play_verticaly_move(engine, engine->grid_size - 1, -1);
  result += join_verticaly_move(engine, engine->grid_size - 1, -1);
  result += play_verticaly_move(engine, engine->grid_size - 1, -1);
  return (result);
}

static uint8_t play_horizontaly_move(t_engine *engine, int32_t start, int32_t way) {
  uint8_t grid_move = 0;
  for (int32_t y = 0; y < engine->grid_size; y++) {
        for (int32_t i = 0; i < engine->grid_size; i++) {
			      int32_t x = start - i * -way;
            int32_t offset = 0;
            uint32_t value = get_tile_coord(engine, x, y);
            if (value) {
              for (int32_t k = 0; k < i; k++) {
                  offset += get_tile_coord(engine, start - k * -way, y) == 0;
              }
              if (offset) {
                set_tile_coord(engine, x, y, 0);
                set_tile_coord(engine, x + offset * -way, y, value);
                grid_move++;
              }
            }
        }
    }
    return grid_move;
}

static uint8_t play_verticaly_move(t_engine *engine, int32_t start, int32_t way) {
  uint8_t grid_move = 0;
  for (int32_t x = 0; x < engine->grid_size; x++) {
        for (int32_t i = 0; i < engine->grid_size; i++) {
			      int32_t y = start - i * -way;
            int32_t offset = 0;
            uint32_t value = get_tile_coord(engine, x, y);
            if (value) {
              for (int32_t k = 0; k < i; k++) {
                  offset += get_tile_coord(engine, x, start - k * -way) == 0;
              }
              if (offset) {
                set_tile_coord(engine, x, y, 0);
                set_tile_coord(engine, x, y + offset * -way, value);
                grid_move++;
              }
            }
        }
    }
    return grid_move;
}

static uint8_t join_horizontaly_move(t_engine *engine, int32_t start, int32_t way) {
    uint8_t grid_move = 0;
    for (int32_t y = 0; y < engine->grid_size; y++) {
        for (int32_t i = 0; i < engine->grid_size - 1; i++) {
			      int32_t x = start - i * -way;
            uint32_t value = get_tile_coord(engine, x, y);
            uint32_t next_value = get_tile_coord(engine, x + way, y);
            if (value && value == next_value) {
                engine->score += value * 2;
                set_tile_coord(engine, x, y, value * 2);
                set_tile_coord(engine, x + way, y, 0);
                grid_move++;
            }
        }
    }
    return grid_move;
}

static uint8_t join_verticaly_move(t_engine *engine, int32_t start, int32_t way) {
    uint8_t grid_move = 0;
    for (int32_t x = 0; x < engine->grid_size; x++) {
        for (int32_t i = 0; i < engine->grid_size - 1; i++) {
			      int32_t y = start - i * -way;
            uint32_t value = get_tile_coord(engine, x, y);
            uint32_t next_value = get_tile_coord(engine, x, y + way);
            if (value && value == next_value) {
                engine->score += value * 2;
                set_tile_coord(engine, x, y, value * 2);
                set_tile_coord(engine, x, y + way, 0);
                grid_move++;
            }
        }
    }
    return grid_move;
}




static bool can_join_horizontaly(t_engine *engine, int32_t start, int32_t way) {
    for (int32_t y = 0; y < engine->grid_size; y++) {
        for (int32_t i = 0; i < engine->grid_size - 1; i++) {
			      int32_t x = start - i * -way;
            uint32_t value = get_tile_coord(engine, x, y);
            uint32_t next_value = get_tile_coord(engine, x + way, y);
            if (value && value == next_value) {
              return true;
            }
        }
    }
    return false;
}


static bool can_join_verticaly(t_engine *engine, int32_t start, int32_t way) {
    for (int32_t x = 0; x < engine->grid_size; x++) {
        for (int32_t i = 0; i < engine->grid_size - 1; i++) {
			      int32_t y = start - i * -way;
            uint32_t value = get_tile_coord(engine, x, y);
            uint32_t next_value = get_tile_coord(engine, x, y + way);
            if (value && value == next_value) {
                return true;
            }
        }
    }
    return false;
}