/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:55:32 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/28 16:25:36 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>

#include "display.h"

static int32_t hex_init_color(uint8_t id, uint32_t rgb);

int8_t initialize_colors(void) {
  start_color();

  if (hex_init_color(COLOR_ID_0, COLOR_0) == ERR ||
      hex_init_color(COLOR_ID_2, COLOR_2) == ERR ||
      hex_init_color(COLOR_ID_4, COLOR_4) == ERR ||
      hex_init_color(COLOR_ID_8, COLOR_8) == ERR ||
      hex_init_color(COLOR_ID_16, COLOR_16) == ERR ||
      hex_init_color(COLOR_ID_32, COLOR_32) == ERR ||
      hex_init_color(COLOR_ID_64, COLOR_64) == ERR ||
      hex_init_color(COLOR_ID_128, COLOR_128) == ERR ||
      hex_init_color(COLOR_ID_256, COLOR_256) == ERR ||
      hex_init_color(COLOR_ID_512, COLOR_512) == ERR ||
      hex_init_color(COLOR_ID_1024, COLOR_1024) == ERR ||
      hex_init_color(COLOR_ID_2048, COLOR_2048) == ERR ||
      hex_init_color(COLOR_ID_BG, COLOR_BG) == ERR ||
      hex_init_color(COLOR_ID_MENU, COLOR_MENU) == ERR)
    return (-1);

  if (init_pair(COLOR_PAIR_0, COLOR_BLACK, COLOR_ID_0) == ERR ||
      init_pair(COLOR_PAIR_2, COLOR_BLACK, COLOR_ID_2) == ERR ||
      init_pair(COLOR_PAIR_4, COLOR_BLACK, COLOR_ID_4) == ERR ||
      init_pair(COLOR_PAIR_8, COLOR_BLACK, COLOR_ID_8) == ERR ||
      init_pair(COLOR_PAIR_16, COLOR_BLACK, COLOR_ID_16) == ERR ||
      init_pair(COLOR_PAIR_32, COLOR_BLACK, COLOR_ID_32) == ERR ||
      init_pair(COLOR_PAIR_64, COLOR_BLACK, COLOR_ID_64) == ERR ||
      init_pair(COLOR_PAIR_128, COLOR_BLACK, COLOR_ID_128) == ERR ||
      init_pair(COLOR_PAIR_256, COLOR_BLACK, COLOR_ID_256) == ERR ||
      init_pair(COLOR_PAIR_512, COLOR_BLACK, COLOR_ID_512) == ERR ||
      init_pair(COLOR_PAIR_1024, COLOR_BLACK, COLOR_ID_1024) == ERR ||
      init_pair(COLOR_PAIR_2048, COLOR_BLACK, COLOR_ID_2048) == ERR ||
      init_pair(COLOR_PAIR_BG, COLOR_BLACK, COLOR_ID_BG) == ERR ||
      init_pair(COLOR_PAIR_SELECTED, COLOR_ID_16, COLOR_ID_BG) == ERR ||
      init_pair(COLOR_PAIR_MENU, COLOR_ID_2, COLOR_ID_MENU) == ERR)
    return (-1);
  return (0);
}

static int32_t hex_init_color(uint8_t id, uint32_t rgb) {
  return init_color(id, RGB_NCURSE(HEX_RED(rgb)), RGB_NCURSE(HEX_GREEN(rgb)),
                    RGB_NCURSE(HEX_BLUE(rgb)));
}

uint8_t get_color_id(int32_t tile_value) {
  switch (tile_value) {
    case 0:
      return COLOR_PAIR_0;
    case 2:
      return COLOR_PAIR_2;
    case 4:
      return COLOR_PAIR_4;
    case 8:
      return COLOR_PAIR_8;
    case 16:
      return COLOR_PAIR_16;
    case 32:
      return COLOR_PAIR_32;
    case 64:
      return COLOR_PAIR_64;
    case 128:
      return COLOR_PAIR_128;
    case 256:
      return COLOR_PAIR_256;
    case 512:
      return COLOR_PAIR_512;
    case 1024:
      return COLOR_PAIR_1024;
    case 2048:
      return COLOR_PAIR_2048;
    default:
      return COLOR_PAIR_2048;
  }
}