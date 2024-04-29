/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scores.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:08:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/28 21:08:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "scores.h"

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "libft.h"

static bool player_is_in_scores(char *username, t_scores *scores);

int8_t update_scores(t_scores *scores, char *username, uint32_t score) {
  free_scores(scores);
  if (read_scores(scores) == -1) {
    return -1;
  }
  if (add_user_score(username, score, scores) == -1) {
    free_scores(scores);
    return -1;
  }
  if (write_scores(scores) == -1) {
    free_scores(scores);
    return -1;
  }
  return 0;
}

int8_t read_scores(t_scores *scores) {
  int32_t fd = open(SCORES_FILE, O_CREAT | O_RDONLY, 0644);
  if (fd < 0) {
    return -1;
  }
  scores->nb_players = 0;
  char *line = get_next_line(fd);
  for (uint8_t i = 0; i < 5 && line; i++) {
    char **split = ft_split(line, ' ');
    free(line);
    if (split == NULL) {
      close(fd);
      return -1;
    }
    if (split[0] == NULL || split[1] == NULL) {
      ft_free_split(split);
      close(fd);
      return -1;
    }
    scores->players[scores->nb_players].username = ft_strdup(split[0]);
    if (scores->players[scores->nb_players].username == NULL) {
      ft_free_split(split);
      close(fd);
      return -1;
    }
    scores->players[scores->nb_players].score = ft_atoi(split[1]);
    scores->nb_players++;
    ft_free_split(split);
    line = get_next_line(fd);
  }
  free(line);
  close(fd);
  if (errno != 0) {
    free_scores(scores);
    return -1;
  }
  return 0;
}

int8_t write_scores(t_scores *scores) {
  int32_t fd = open(SCORES_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  uint32_t result = 0;
  if (fd < 0) {
    return -1;
  }
  for (uint32_t i = 0; i < scores->nb_players; i++) {
    result += write(fd, scores->players[i].username,
                    ft_strlen(scores->players[i].username)) != -1;
    result += write(fd, " ", 1) != -1;
    char *score = ft_itoa(scores->players[i].score);
    if (score == NULL) {
      close(fd);
      return -1;
    }
    result += write(fd, score, ft_strlen(score)) != -1;
    result += write(fd, "\n", 1) != -1;
    free(score);
    if (result != 4) {
      close(fd);
      return -1;
    }
  }
  close(fd);
  return 0;
}

int8_t add_user_score(char *username, uint32_t score, t_scores *scores) {
  remove_user_lower_score(username, score, scores);
  if (player_is_in_scores(username, scores)) {
    return 0;
  }
  int32_t insert_index = -1;
  if (scores->nb_players < 5) {
    insert_index = scores->nb_players;
  }
  for (uint32_t i = 0; i < scores->nb_players; i++) {
    if (score > scores->players[i].score) {
      insert_index = i;
      break;
    }
  }
  if (insert_index == -1) {
    return 0;
  }
  for (uint32_t i = scores->nb_players; i > (uint32_t)insert_index; i--) {
    if (i == 5) {
      free(scores->players[i - 1].username);
      scores->players[i - 1].username = NULL;
      continue;
    }
    scores->players[i] = scores->players[i - 1];
  }
  scores->players[insert_index].username = ft_strdup(username);
  if (scores->players[insert_index].username == NULL) {
    return -1;
  }
  scores->players[insert_index].score = score;
  scores->nb_players++;
  return 1;
}

void remove_user_lower_score(char *username, uint32_t score, t_scores *scores) {
  for (uint32_t i = 0; i < scores->nb_players; i++) {
    if (ft_strcmp(username, scores->players[i].username) == 0 &&
        score > scores->players[i].score) {
      free(scores->players[i].username);
      scores->players[i].username = NULL;
      for (uint32_t j = i; j < scores->nb_players - 1; j++) {
        scores->players[j] = scores->players[j + 1];
      }
      scores->nb_players--;
      return;
    }
  }
}

void free_scores(t_scores *scores) {
  for (uint32_t i = 0; i < scores->nb_players; i++) {
    free(scores->players[i].username);
    scores->players[i].username = NULL;
    scores->players[i].score = 0;
  }
}

static bool player_is_in_scores(char *username, t_scores *scores) {
  for (uint32_t i = 0; i < scores->nb_players; i++) {
    if (ft_strcmp(username, scores->players[i].username) == 0) {
      return true;
    }
  }
  return false;
}