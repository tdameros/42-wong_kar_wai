/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/28 19:23:47 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "libft.h"

#include "display.h"
#include "engine.h"
#include "grid.h"
#include "scores.h"

int main(int argc, char **argv) {

  setlocale(LC_ALL, "");
  uint8_t victory = false;
  initscr();
  assume_default_colors(COLOR_ID_BG, COLOR_ID_BG);
  curs_set(0);

  initialize_colors();
  // start_color();

  // hex_init_color(1, 0x84e387);
  // init_color(COLOR_ID_2, 518, 890, 529);
  // init_pair(COLOR_PAIR_2, COLOR_BLACK, COLOR_ID_2);
  keypad(stdscr, TRUE);
  t_engine engine;
  if (argc >= 2) {
    engine = initialize_engine(argv[1], 4);
  } else {
    engine = initialize_engine("undefined", 4);
  }
  if (read_scores(&engine.best_scores) == -1) {
    ft_putstr_fd("Error reading scores\n", STDERR_FILENO);
    return -1;
  }

  place_random_tile(&engine);
  place_random_tile(&engine);

  int32_t c = 0;
  print_menu(engine.menu, &engine, engine.selected_button);
  refresh();
  while (c != KEY_ESC) {
    c = getch();
    if (engine.menu == NO_MENU && play_move(&engine, c) &&
        (c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT)) {
      place_random_tile(&engine);
      if (update_scores(&engine.best_scores, engine.username, engine.score) == -1) {
        ft_putstr_fd("Error updating scores\n", STDERR_FILENO);
        return -1;
      }
    } else {
      menu_callback(&engine, c);
    }
    if (!can_play(&engine)) {
      engine.menu = LOOSE_MENU;
    }
    if (!engine.win && is_win(&engine)) {
      engine.menu = WIN_MENU;
      engine.win = true;
    }
    print_menu(engine.menu, &engine, engine.selected_button);
    refresh();
  }
  endwin();
  printf("Victory = %d\n", victory);
  return 0;
}
