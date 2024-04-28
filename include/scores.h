/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scores.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:09:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/28 21:09:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INC_42_WONG_KAR_WAI_INCLUDE_SCORES_H_
#define INC_42_WONG_KAR_WAI_INCLUDE_SCORES_H_

#include <stdint.h>
#include <stdbool.h>

# define SCORES_FILE ".scores"

typedef struct s_player {
  char *username;
  uint32_t score;
} t_player;

typedef struct s_scores {
  t_player players[5];
  uint32_t nb_players;
} t_scores;

int8_t update_scores(t_scores *scores, char *username, uint32_t score);
int8_t read_scores(t_scores *scores);
int8_t write_scores(t_scores *scores);
int8_t add_user_score(char *username, uint32_t score, t_scores *scores);
void remove_user_lower_score(char *username, uint32_t score, t_scores *scores);
void free_scores(t_scores *scores);

#endif