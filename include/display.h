/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:30:31 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/28 19:50:18 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

// #include "engine.h"
#include <stdint.h>
typedef struct s_engine t_engine;

#define GRID_MARGIN 3
#define MENU_MARGIN 5
#define MENU_MARGIN_HORIZONTALY 0
#define MENU_MARGIN_VERTICALY (GRID_MARGIN + 8)

#define KEY_ESC 27
#define KEY_RETURN 10
#define RGB_TO_TERM_COLOR(x) (x * 4.f) 

# define RGB_NCURSE(x) (x * RGB_NCURSE_RATE)
# define RGB_NCURSE_RATE 3.9215f

#define HEX_RED(rgb) ((rgb & HEX_RED_MASK) >> HEX_RED_OFFSET) 
#define HEX_RED_MASK 0xFF0000
#define HEX_RED_OFFSET 16

#define HEX_GREEN(rgb) ((rgb & HEX_GREEN_MASK) >> HEX_GREEN_OFFSET) 
#define HEX_GREEN_MASK 0x00FF00
#define HEX_GREEN_OFFSET 8

#define HEX_BLUE(rgb) ((rgb & HEX_BLUE_MASK) >> HEX_BLUE_OFFSET) 
#define HEX_BLUE_MASK 0x0000FF
#define HEX_BLUE_OFFSET 0

typedef enum e_color_id {
   	COLOR_ID_0 = 10,
	COLOR_ID_2,
	COLOR_ID_4,
	COLOR_ID_8,
	COLOR_ID_16,
	COLOR_ID_32,
	COLOR_ID_64,
	COLOR_ID_128,
	COLOR_ID_256,
	COLOR_ID_512,
	COLOR_ID_1024,
	COLOR_ID_2048,
	COLOR_ID_BG,
	COLOR_ID_MENU,
}   t_color_id; 

typedef enum e_color_pair {
    COLOR_PAIR_0 = 1,
	COLOR_PAIR_2,
	COLOR_PAIR_4,
	COLOR_PAIR_8,
	COLOR_PAIR_16,
	COLOR_PAIR_32,
	COLOR_PAIR_64,
	COLOR_PAIR_128,
	COLOR_PAIR_256,
	COLOR_PAIR_512,
	COLOR_PAIR_1024,
	COLOR_PAIR_2048,
	COLOR_PAIR_BG,
	COLOR_PAIR_MENU,
	COLOR_PAIR_SELECTED,
}   t_color_pair; 


typedef enum e_color {
	COLOR_0 = 0xCCC0B3,
    COLOR_2 = 0xEEE4DA,
	COLOR_4 = 0xEDE0C9,
	COLOR_8 = 0xF2B178,
	COLOR_16 = 0xFB9663,
	COLOR_32 = 0xF67C5f,
	COLOR_64 = 0xF65E3B,
	COLOR_128 = 0xEDCF72,
	COLOR_256 = 0xEECC63,
	COLOR_512 = 0xECC851,
	COLOR_1024 = 0xEBC541,
	COLOR_2048 = 0xEEC22E,
	COLOR_BG = 0xBCACA1,
	COLOR_MENU = 0x938B82,
}   t_color; 

typedef enum e_menu {
	START_MENU = 0,
	NO_MENU,
	WIN_MENU,
	LOOSE_MENU,
        SCORES_MENU,
}	t_menu;

typedef enum e_button {
	BUTTON1 = 0,
	BUTTON2,
	BUTTON3,
	BUTTON4,
}	t_button;

typedef enum e_ascii_len {
	ASCII_0 = 9,
	ASCII_1 = 4,
	ASCII_2 = 8,
	ASCII_3 = 8,
	ASCII_4 = 8,
	ASCII_5 = 8,
	ASCII_6 = 9,
	ASCII_7 = 8,
	ASCII_8 = 8,
	ASCII_9 = 8,
} t_ascii_len;

void print_grid(t_engine *engine);
int8_t initialize_colors(void);
void print_menu(t_menu type, t_engine *engine, int8_t selected);
uint8_t get_color_id(int32_t tile_value);
void menu_callback(t_engine *engine, int32_t key);
uint32_t ft_nbrlen(uint32_t value);


#endif