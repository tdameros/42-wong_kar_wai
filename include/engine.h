/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:51:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/28 19:05:00 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WONG_KAR_WAI_H
# define WONG_KAR_WAI_H

# include <stdint.h>
# include <stdbool.h>

# include "display.h"
# include "scores.h"

# define MAX_GRID_SIZE 10
# define MIN_GRID_SIZE 4
# define GRID_BUFFER_SIZE (MAX_GRID_SIZE * MAX_GRID_SIZE)
# define USERNAME_MAX_LENGTH 8
# define SCORES_FILE ".scores"
# define USERNAME_BUFFER_SIZE (USERNAME_MAX_LENGTH + 1)
#define NEW_TILE 2

enum e_const
{
	WIN_VALUE = 8
};

typedef struct s_engine
{
	uint32_t score;
        char *username;
	uint32_t moves;
	int32_t grid_size;
	uint32_t grid[GRID_BUFFER_SIZE];
	t_menu menu;
	t_button selected_button;
	bool win;
        t_scores best_scores;
} t_engine;

t_engine initialize_engine(char *username, uint32_t grid_size);
bool can_play(t_engine *engine);
bool is_win(t_engine *engine);

#endif