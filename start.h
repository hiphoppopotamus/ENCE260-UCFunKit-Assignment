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
 */
void start_game (void);

#endif
