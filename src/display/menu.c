/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:56:48 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/28 23:01:23 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>

#include "display.h"
#include "engine.h"
#include "grid.h"

static void print_win_ascii(uint32_t x, uint32_t y);
static void print_win_menu(t_engine *engine, int8_t selected);
static void win_menu_callback(t_engine *engine, int32_t key);
static void print_start_ascii(uint32_t x, uint32_t y);
static void print_start_menu(t_engine *engine, int8_t selected);
static void print_loose_menu(t_engine *engine, int8_t selected);
static void start_menu_callback(t_engine *engine, int32_t key);
static void print_loose_ascii(uint32_t x, uint32_t y);
static void increment_grid_size(t_engine *engine);
static void decrement_grid_size(t_engine *engine);
static void loose_menu_callback(int32_t key);
static void print_score_ascii(uint32_t x, uint32_t y);
static void print_score_menu(t_engine *engine, int8_t selected);
static uint32_t ft_strlen(char *str);

void menu_callback(t_engine *engine, int32_t key) {
  switch (engine->menu) {
    case (WIN_MENU):
      win_menu_callback(engine, key);
      break;
    case (START_MENU):
      start_menu_callback(engine, key);
      break;
    case (LOOSE_MENU):
      loose_menu_callback(key);
      break;
    default:
      break;
  }
}

void print_menu(t_menu type, t_engine *engine, int8_t selected) {
  switch (type) {
    case NO_MENU:
      print_grid(engine);
      break;
    case WIN_MENU:
      print_win_menu(engine, selected);
      break;
    case LOOSE_MENU:
      print_loose_menu(engine, selected);
      break;
    case START_MENU:
      print_start_menu(engine, selected);
      break;
	case SCORES_MENU:
      print_score_menu(engine, selected);
      break;
    default:
      break;
  }
}

static void print_win_menu(t_engine *engine, int8_t selected) {
  print_grid(engine);
  uint32_t height, width, size_x, size_y;
  (void)engine;
  getmaxyx(stdscr, height, width);

  size_x = (width / 2 > height ? height - MENU_MARGIN * 2
                               : width / 2 - MENU_MARGIN * 2) *
           2;
  size_y = size_x / 2 - (size_x / 2 * 0.45f);
  attron(COLOR_PAIR(COLOR_PAIR_MENU));
  uint32_t x_start = (width - size_x) / 2;
  uint32_t y_start = (height - size_y) / 2;
  for (uint32_t y = y_start; y < size_y + y_start + 1; y++) {
    for (uint32_t x = x_start; x < size_x + x_start + 1; x++) {
      if (x == x_start && y == y_start)
        mvprintw(y, x, "┌");
      else if (x == size_x + x_start && y == y_start)
        mvprintw(y, x, "┐");
      else if (x == x_start && y == size_y + y_start)
        mvprintw(y, x, "└");
      else if (x == size_x + x_start && y == size_y + y_start)
        mvprintw(y, x, "┘");
      else if (x == x_start || x == size_x + x_start)
        mvprintw(y, x, "│");
      else if (y == y_start || y == size_y + y_start)
        mvprintw(y, x, "─");
      else
        mvprintw(y, x, " ");
    }
  }
  if (size_x > 48) {
    print_win_ascii(x_start + ((size_x - 48) / 2), y_start + 3);
  } else {
    mvprintw(y_start + 5, x_start + ((size_x - 8) / 2), "You Win!");
  }

  if (selected == BUTTON1)
    mvprintw(y_start + size_y - 5, x_start + ((size_x - 14) / 2),
             "» Continue «");
  else
    mvprintw(y_start + size_y - 5, x_start + ((size_x - 14) / 2),
             "  Continue  ");
  if (selected == BUTTON2)
    mvprintw(y_start + size_y - 3, x_start + ((size_x - 10) / 2), "» Exit «");
  else
    mvprintw(y_start + size_y - 3, x_start + ((size_x - 10) / 2), "  Exit  ");

  attroff(COLOR_PAIR(COLOR_PAIR_MENU));
}

static void win_menu_callback(t_engine *engine, int32_t key) {
  if (key == KEY_UP) {
    engine->selected_button = (engine->selected_button - 1) % 2;
  } else if (key == KEY_DOWN) {
    engine->selected_button = (engine->selected_button + 1) % 2;
  } else if (key == KEY_RETURN && engine->selected_button == BUTTON1) {
    engine->menu = NO_MENU;
  } else if (key == KEY_RETURN && engine->selected_button == BUTTON2) {
    endwin();
    exit(0);
  }
}

static void start_menu_callback(t_engine *engine, int32_t key) {
  if (key == KEY_UP) {
    engine->selected_button = (engine->selected_button - 1) % 4;
  } else if (key == KEY_DOWN) {
    engine->selected_button = (engine->selected_button + 1) % 4;
  } else if (key == KEY_RETURN && engine->selected_button == BUTTON1) {
    engine->menu = NO_MENU;
	place_random_tile(engine);
  	place_random_tile(engine);
  } else if (key == KEY_RETURN && engine->selected_button == BUTTON2) {
    engine->menu = SCORES_MENU;
  } else if (key == KEY_LEFT && engine->selected_button == BUTTON3) {
    decrement_grid_size(engine);
  } else if (key == KEY_RIGHT && engine->selected_button == BUTTON3) {
    increment_grid_size(engine);
  } else if (key == KEY_RETURN && engine->selected_button == BUTTON3) {
    engine->menu = NO_MENU;
	place_random_tile(engine);
  	place_random_tile(engine);
  } else if (key == KEY_RETURN && engine->selected_button == BUTTON4) {
    endwin();
    exit(0);
  }
}

static void increment_grid_size(t_engine *engine) {
  engine->grid_size++;
  if (engine->grid_size > MAX_GRID_SIZE) {
    engine->grid_size = MIN_GRID_SIZE;
  }
}

static void decrement_grid_size(t_engine *engine) {
  engine->grid_size--;
  if (engine->grid_size < MIN_GRID_SIZE) {
    engine->grid_size = MAX_GRID_SIZE;
  }
}

static void print_win_ascii(uint32_t x, uint32_t y) {
  mvprintw(y, x, "__  __                 _       __ _           __");
  mvprintw(y + 1, x, "\\ \\/ /____   __  __   | |     / /(_)____     / /");
  mvprintw(y + 2, x, " \\  // __ \\ / / / /   | | /| / // // __ \\   / / ");
  mvprintw(y + 3, x, " / // /_/ // /_/ /    | |/ |/ // // / / /  /_/  ");
  mvprintw(y + 4, x, "/_/ \\____/ \\__,_/     |__/|__//_//_/ /_/  (_)   ");
}

static void print_start_menu(t_engine *engine, int8_t selected) {
  uint32_t height, width, size_x, size_y;
  getmaxyx(stdscr, height, width);

  size_x = width;
  size_y = height;
  attron(COLOR_PAIR(COLOR_PAIR_MENU));
  uint32_t x_start = (width - size_x) / 2;
  uint32_t y_start = (height - size_y) / 2;
  for (uint32_t y = y_start; y < size_y + y_start; y++) {
    for (uint32_t x = x_start; x < size_x + x_start; x++) {
      if (x == x_start && y == y_start)
        mvprintw(y, x, "┌");
      else if (x == size_x + x_start - 1 && y == y_start)
        mvprintw(y, x, "┐");
      else if (x == x_start && y == size_y + y_start - 1)
        mvprintw(y, x, "└");
      else if (x == size_x + x_start - 1 && y == size_y + y_start - 1)
        mvprintw(y, x, "┘");
      else if (x == x_start || x == size_x + x_start - 1)
        mvprintw(y, x, "│");
      else if (y == y_start || y == size_y + y_start - 1)
        mvprintw(y, x, "─");
      else
        mvprintw(y, x, " ");
    }
  }
  if (size_x > 83) {
    print_start_ascii(x_start + ((size_x - 83) / 2), y_start + 3);
  } else {
    mvprintw(y_start + 5, x_start + ((size_x - 6) / 2), "2048 !");
  }

  if (selected == BUTTON1)
    mvprintw(y_start + size_y - 10, x_start + ((size_x - 11) / 2), "» Start «");
  else
    mvprintw(y_start + size_y - 10, x_start + ((size_x - 11) / 2), "  Start  ");
  if (selected == BUTTON2)
    mvprintw(y_start + size_y - 7, x_start + ((size_x - 11) / 2), "» Score «");
  else
    mvprintw(y_start + size_y - 7, x_start + ((size_x - 11) / 2), "  Score  ");
  if (selected == BUTTON3)
    mvprintw(y_start + size_y - 5, x_start + ((size_x - 19) / 2),
             "» Grid size : %d «", engine->grid_size);
  else
    mvprintw(y_start + size_y - 5, x_start + ((size_x - 19) / 2),
             "  Grid size : %d  ", engine->grid_size);
  if (selected == BUTTON4)
    mvprintw(y_start + size_y - 3, x_start + ((size_x - 10) / 2), "» Exit «");
  else
    mvprintw(y_start + size_y - 3, x_start + ((size_x - 10) / 2), "  Exit  ");

  attroff(COLOR_PAIR(COLOR_PAIR_MENU));
}

static void print_start_ascii(uint32_t x, uint32_t y) {
  mvprintw(y, x,
           "____/\\\\\\\\\\\\\\\\\\__________/\\\\\\\\\\\\\\________________/"
           "\\\\\\_________/\\\\\\\\\\\\\\\\\\____        ");
  mvprintw(y + 1, x,
           " __/\\\\\\///////\\\\\\______/\\\\\\/////\\\\\\____________/"
           "\\\\\\\\\\_______/\\\\\\///////\\\\\\__       ");
  mvprintw(y + 2, x,
           "  "
           "_\\///______\\//\\\\\\____/\\\\\\____\\//\\\\\\_________/\\\\\\/"
           "\\\\\\______\\/\\\\\\_____\\/\\\\\\__      ");
  mvprintw(y + 3, x,
           "   "
           "___________/\\\\\\/____\\/\\\\\\_____\\/\\\\\\_______/\\\\\\/\\/"
           "\\\\\\______\\///\\\\\\\\\\\\\\\\\\/___     ");
  mvprintw(y + 4, x,
           "    "
           "________/\\\\\\//______\\/\\\\\\_____\\/\\\\\\_____/\\\\\\/__\\/"
           "\\\\\\_______/\\\\\\///////\\\\\\__    ");
  mvprintw(y + 5, x,
           "     "
           "_____/\\\\\\//_________\\/\\\\\\_____\\/\\\\\\___/"
           "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\______\\//\\\\\\_   ");
  mvprintw(y + 6, x,
           "      "
           "___/\\\\\\/____________\\//\\\\\\____/\\\\\\___\\///////////\\\\\\/"
           "/___\\//\\\\\\______/\\\\\\__  ");
  mvprintw(y + 7, x,
           "       "
           "__/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\___\\///\\\\\\\\\\\\\\/"
           "______________\\/\\\\\\______\\///\\\\\\\\\\\\\\\\\\/___ ");
  mvprintw(y + 8, x,
           "        "
           "_\\///////////////______\\///////________________\\///_________\\//"
           "///////_____");
}

static void print_loose_menu(t_engine *engine, int8_t selected) {
  print_grid(engine);
  uint32_t height, width, size_x, size_y;
  getmaxyx(stdscr, height, width);

  size_x = (width / 2 > height ? height - MENU_MARGIN * 2
                               : width / 2 - MENU_MARGIN * 2) *
           2;
  size_y = size_x / 2 - (size_x / 2 * 0.45f);
  attron(COLOR_PAIR(COLOR_PAIR_MENU));
  uint32_t x_start = (width - size_x) / 2;
  uint32_t y_start = (height - size_y) / 2;
  for (uint32_t y = y_start; y < size_y + y_start + 1; y++) {
    for (uint32_t x = x_start; x < size_x + x_start + 1; x++) {
      if (x == x_start && y == y_start)
        mvprintw(y, x, "┌");
      else if (x == size_x + x_start && y == y_start)
        mvprintw(y, x, "┐");
      else if (x == x_start && y == size_y + y_start)
        mvprintw(y, x, "└");
      else if (x == size_x + x_start && y == size_y + y_start)
        mvprintw(y, x, "┘");
      else if (x == x_start || x == size_x + x_start)
        mvprintw(y, x, "│");
      else if (y == y_start || y == size_y + y_start)
        mvprintw(y, x, "─");
      else
        mvprintw(y, x, " ");
    }
  }

  mvprintw(y_start + size_y - 5, x_start + ((size_x - (ft_nbrlen(engine->score) + 13)) / 2), "Your score : %d", engine->score);

  if (size_x > 55) {
    print_loose_ascii(x_start + ((size_x - 55) / 2), y_start + 3);
  } else {
    mvprintw(y_start + 5, x_start + ((size_x - 8) / 2), "You Win!");
  }

  if (selected == BUTTON1)
    mvprintw(y_start + size_y - 3, x_start + ((size_x - 10) / 2), "» Exit «");
  else
    mvprintw(y_start + size_y - 3, x_start + ((size_x - 10) / 2), "  Exit  ");

  attroff(COLOR_PAIR(COLOR_PAIR_MENU));
}

static void loose_menu_callback(int32_t key) {
  if (key == KEY_RETURN) {
    endwin();
    exit(0);
  }
}

static void print_loose_ascii(uint32_t x, uint32_t y) {
  mvprintw(y, x, " __   __              _                              _ ");
  mvprintw(y + 1, x,
           " \\ \\ / /___   _   _  | |     ___    ___   ___   ___ | |");
  mvprintw(y + 2, x,
           "  \\ V // _ \\ | | | | | |    / _ \\  / _ \\ / __| / _ \\| |");
  mvprintw(y + 3, x,
           "   | || (_) || |_| | | |___| (_) || (_) |\\__ \\|  __/|_|");
  mvprintw(y + 4, x,
           "   |_| \\___/  \\__,_| |_____|\\___/  \\___/ |___/ \\___|(_)");
}

static void print_score_menu(t_engine *engine, int8_t selected) {
  uint32_t height, width, size_x, size_y;
  getmaxyx(stdscr, height, width);

  size_x = (width / 2 > height ? height - MENU_MARGIN * 2
                               : width / 2 - MENU_MARGIN * 2) *
           2;
  size_y = size_x / 2 - (size_x / 2 * 0.45f);
  attron(COLOR_PAIR(COLOR_PAIR_MENU));
  uint32_t x_start = (width - size_x) / 2;
  uint32_t y_start = (height - size_y) / 2;
  for (uint32_t y = y_start; y < size_y + y_start + 1; y++) {
    for (uint32_t x = x_start; x < size_x + x_start + 1; x++) {
      if (x == x_start && y == y_start)
        mvprintw(y, x, "┌");
      else if (x == size_x + x_start && y == y_start)
        mvprintw(y, x, "┐");
      else if (x == x_start && y == size_y + y_start)
        mvprintw(y, x, "└");
      else if (x == size_x + x_start && y == size_y + y_start)
        mvprintw(y, x, "┘");
      else if (x == x_start || x == size_x + x_start)
        mvprintw(y, x, "│");
      else if (y == y_start || y == size_y + y_start)
        mvprintw(y, x, "─");
      else
        mvprintw(y, x, " ");
    }
  }
	
	(void) engine;
	for (uint32_t i = 0; i < engine->scores.nb_players; i++)
	{
  		mvprintw(y_start + 10 + 2 * i, x_start + ((size_x - (ft_nbrlen(engine->scores.players[i].score) + ft_strlen(engine->scores.players[i].username) + 3)) / 2),
		"%s : %d", engine->scores.players[i].username, engine->scores.players[i].score);
		
	}
	

  if (size_x > 32) {
    print_score_ascii(x_start + ((size_x - 32) / 2), y_start + 3);
  } else {
    mvprintw(y_start + 5, x_start + ((size_x - 6) / 2), "Score");
  }

  if (selected == BUTTON1)
    mvprintw(y_start + size_y - 3, x_start + ((size_x - 10) / 2), "» Exit «");
  else
    mvprintw(y_start + size_y - 3, x_start + ((size_x - 10) / 2), "  Exit  ");

  attroff(COLOR_PAIR(COLOR_PAIR_MENU));
}

static uint32_t ft_strlen(char *str)
{
	uint32_t size = 0;
	while (str[size])
		size++;
	return size;
}

static void print_score_ascii(uint32_t x, uint32_t y) {
  mvprintw(y + 0, x, "  ____                          ");
  mvprintw(y + 1, x, " / ___|  ___ ___  _ __ ___  ___ ");
  mvprintw(y + 2, x, " \\___ \\ / __/ _ \\| '__/ _ \\/ __|");
  mvprintw(y + 3, x, "  ___) | (_| (_) | | |  __/\\__ \\");
  mvprintw(y + 4, x, " |____/ \\___\\___/|_|  \\___||___/");
}