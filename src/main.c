/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/27 16:44:43 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "display.h"
#include "engine.h"
#include "grid.h"

int main(void) {
  t_engine engine = initialize_engine("bwisniew", 4);

  place_random_tile(&engine);
  place_random_tile(&engine);
  place_random_tile(&engine);
  place_random_tile(&engine);
  place_random_tile(&engine);
  // place_random_tile(&engine);
  print_grid(&engine);
  printf("\n\n\n");
  play_move(&engine, UP);
  print_grid(&engine);
  printf("\n\n\n");
  // play_move(&engine, RIGHT);
  // print_grid(&engine);
  // printf("\n\n\n");
  // play_move(&engine, LEFT);
  // print_grid(&engine);
  return 0;
}
