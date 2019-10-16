/** GROUP 307 ewi45 cjm356
    @file   io_init_update.c
    @author Euan Widaja, Cam Maslin
    @date   16 October 2019
    @brief  Initialises and updates all inputs and outputs for the program.
*/


#include "io_init_update.h"

/**
 * Initialises the fun kit's key functionalities:
 * system, button, navswitch, ir_uart, ledmat, tinygl, pacer, and led.
 * led_set (LED1, 0) is called to turn led off,
 * as initialising led turns it on by default.
 */
void io_initialise (void)
{
    system_init ();
    button_init ();
    display_init ();
    navswitch_init ();
    ir_uart_init ();
    tinygl_init (PACER_RATE);
    pacer_init (PACER_RATE);
    led_init ();
    led_set (LED1, 0);
    ledmat_init ();
}

/**
 * A method that updates tinygl, navswitch, button,
 * and calls pacer_wait().
 */
void io_update (void)
{
    pacer_wait ();
    tinygl_update ();
    navswitch_update ();
    button_update ();
}
