/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/28 22:03:26 by bwisniew         ###   ########.fr       */
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

  if (!setlocale(LC_ALL, ""))
    return (1);
  initscr();
  if (
    assume_default_colors(COLOR_BLACK, COLOR_ID_BG) == ERR ||
    curs_set(0) == ERR ||
    initialize_colors() < 0 ||
    keypad(stdscr, TRUE) == ERR
  )
  {
    endwin();
    return (1);
  }
  t_engine engine = initialize_engine("bwisniew", 4);
  int32_t c = 0;
  print_menu(engine.menu, &engine, engine.selected_button);
  refresh();
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
    refresh();
  }
  endwin();
  return 0;
}
