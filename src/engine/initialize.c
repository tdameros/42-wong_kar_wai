#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "engine.h"

t_engine initialize_engine(char *username, uint32_t grid_size) {
  t_engine engine;
  uint8_t *engine_ptr = (uint8_t *)&engine;

  for (uint16_t i = 0; i < sizeof(engine); i++) {
    engine_ptr[i] = 0;
  }
  engine.grid_size = grid_size;
  engine.username = username;
  srand(time(NULL));
  start_color();
  return engine;
}
