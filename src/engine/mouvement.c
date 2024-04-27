#include "engine.h"
#include "grid.h"

static void play_horizontaly_move(t_engine *engine, int32_t start, int32_t way);
static void join_horizontaly_move(t_engine *engine, int32_t start, int32_t way);

void play_move(t_engine *engine, t_move move) {
    switch (move)
    {
    case RIGHT:
        play_horizontaly_move(engine, engine->grid_size - 1, -1);
        join_horizontaly_move(engine, engine->grid_size - 1, -1);
        play_horizontaly_move(engine, engine->grid_size - 1, -1);
        break;
    case LEFT:
        play_horizontaly_move(engine, 0, 1);
        join_horizontaly_move(engine, 0, 1);
        play_horizontaly_move(engine, 0, 1);
    default:
        break;
    }
}

static void play_horizontaly_move(t_engine *engine, int32_t start, int32_t way) {
	for (int32_t y = 0; y < engine->grid_size; y++) {
        for (int32_t i = 0; i < engine->grid_size; i++) {
			int32_t x = start - i * -way;
            int32_t offset = 0;
            for (int32_t k = 0; k < i; k++) {
                offset += get_tile_coord(engine, start - k * -way, y) == 0;
            }
            uint32_t value = get_tile_coord(engine, x, y);
            set_tile_coord(engine, x, y, 0);
            set_tile_coord(engine, x + offset * -way, y, value);
        }
    }
}

static void join_horizontaly_move(t_engine *engine, int32_t start, int32_t way) {
    for (int32_t y = 0; y < engine->grid_size; y++) {
        for (int32_t i = 0; i < engine->grid_size - 1; i++) {
			int32_t x = start - i * -way;
            uint32_t value = get_tile_coord(engine, x, y);
            uint32_t next_value = get_tile_coord(engine, x + way, y);
            if (value == next_value) {
                set_tile_coord(engine, x, y, value * 2);
                set_tile_coord(engine, x + way, y, 0);
            }
        }
    }
}
