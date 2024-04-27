/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/27 15:58:07 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "engine.h"
#include "grid.h"
#include "display.h"

int main(void){
    t_engine engine = initialize_engine("bwisniew", 4);

    place_random_tile(&engine);
    place_random_tile(&engine);
    place_random_tile(&engine);
    place_random_tile(&engine);
    place_random_tile(&engine);
    //place_random_tile(&engine);
    print_grid(&engine);
    printf("\n\n\n");
    play_move(&engine, LEFT);
    print_grid(&engine);
    printf("\n\n\n");
    play_move(&engine, RIGHT);
    print_grid(&engine);
    printf("\n\n\n");
    // play_move(&engine, LEFT);
    // print_grid(&engine);
    return 0;
}
