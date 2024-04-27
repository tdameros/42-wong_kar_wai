/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/28 00:36:51 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
 #include <unistd.h>
 
#include "display.h"
#include "engine.h"
#include "grid.h"

#include <stdio.h>

int main(void) {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    
    keypad(stdscr,TRUE);
    t_engine engine = initialize_engine("bwisniew", 4);

  place_random_tile(&engine);
  place_random_tile(&engine);
 
  
  int32_t c = 0;
  int8_t res = 0;
  print_grid(&engine);
  while (c != 27)
  {
    c = getch();
    if (c == KEY_UP)
      res = play_move(&engine, UP);
    else if (c == KEY_DOWN)
      res = play_move(&engine, DOWN);
    else if (c == KEY_LEFT)
      res = play_move(&engine, LEFT);
    else if (c == KEY_RIGHT)
      res = play_move(&engine, RIGHT);
    if (res)
    {
      place_random_tile(&engine);
      print_grid(&engine);
    }
  }
    endwin();
  echo();
  return 0;
}
