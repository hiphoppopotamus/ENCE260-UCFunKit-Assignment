/** GROUP 307 ewi45 cjm356
    @file   io_init_update.c
    @author Euan Widaja, Cam Maslin
    @date   16 October 2019
    @brief  Initialises and updates all inputs and outputs for the program.

    @note   Contains functions related to io initialisation and updating.
*/


#ifndef IO_UPDATE_H
#define IO_UPDATE_H

#define PACER_RATE 500

#include "system.h"
#include "display.h"
#include "ir_uart.h"
#include "led.h"
#include "ledmat.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "button.h"


/**
 * Initialises the fun kit's key functionalities:
 * system, button, navswitch, ir_uart, ledmat, tinygl, pacer, and led.
 * led_set (LED1, 0) is called to turn led off,
 * as initialising led turns it on by default.
 */
void io_initialise (void);


/**
 * A method that updates tinygl, navswitch, button,
 * and calls pacer_wait ().
 */
void io_update (void);


#endif
