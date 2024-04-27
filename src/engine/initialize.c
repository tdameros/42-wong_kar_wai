#include "engine.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

static uint32_t get_best_score(char *score_file);
static void initialize_username(t_engine *engine, char *username);

t_engine initialize_engine(char *username, uint32_t grid_size) {
	t_engine engine;
	uint8_t *engine_ptr = (uint8_t *) &engine;

	for (uint16_t i = 0; i < sizeof(engine); i++) {
		engine_ptr[i] = 0;
	}
	engine.best_score = get_best_score(SCORES_FILE);
	engine.grid_size = grid_size;
	initialize_username(&engine, username);
	srand(time(NULL));
	return engine;
}

static uint32_t get_best_score(char *score_file) {
	(void) score_file;
	return 0;
}

static void initialize_username(t_engine *engine, char *username) {
	for (uint8_t i = 0; i < USERNAME_BUFFER_SIZE; i++) {
		engine->username[i] = username[i];
	}
}

