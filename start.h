/** GROUP 307 ewi45 cjm356
    @file   start.c
    @author Euan Widaja, Cam Maslin
    @date   16 October 2019
    @brief  Starts game of Rock Papers Scissors
*/


#ifndef START_H
#define START_H

#include <stdbool.h>

#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "led.h"
#include <avr/io.h>

#include "io_init_update.h"
#include "display_screen.h"
#include "set.h"


/**
 * Key function that starts game.
 *
 * Calls a function display_round () that starts each round.
 * Runs through each round until both players have selected an option.
 * Updates and displays the scoreboard based on the outcome of that round.
 * Repeats the above process, until either score is 6,
 * or round exceeds the maximum possible round (10).
 */
void start_game (void);


#endif
