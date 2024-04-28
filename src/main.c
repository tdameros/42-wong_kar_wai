/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/28 21:36:17 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "display.h"
#include "engine.h"
#include "grid.h"

int main(void) {
  setlocale(LC_ALL, "");
  initscr();
  assume_default_colors(COLOR_BLACK, COLOR_ID_BG);
  curs_set(0);

  initialize_colors();
  keypad(stdscr, TRUE);
  t_engine engine = initialize_engine("bwisniew", 4);
  int32_t c = 0;
  print_menu(engine.menu, &engine, engine.selected_button);
  while (c != KEY_ESC) {
    c = getch();
    if (engine.menu == NO_MENU && play_move(&engine, c) &&
        (c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT)) {
      place_random_tile(&engine);
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
  }
  endwin();
  return 0;
}
