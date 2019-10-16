/** GROUP 307 ewi45 cjm356
    @file   game.c
    @author Euan Widaja, Cam Maslin
    @date   9 October 2019
    @brief  A simple rock, paper, scissors game with a maximum of
            9 rounds and a score board.

    @defgroup game A simple rock, paper, scissors game .
*/

#include "io_init_update.h"
#include "display_screen.h"
#include "set.h"
#include "start.h"


/**
 * Enum that defines a state in which the game is in.
 * STATE_TITLE: Title Screen
 * STATE_START: Start Screen
 */
typedef enum {
    STATE_TITLE,
    STATE_START
} state_t;


/**
 * Main function for the "ROCK, PAPER, SCISSORS" game.
 */
int main (void)
{
    io_initialise();
    state_t state = STATE_TITLE;
    while (1) {
        io_update();
        switch (state) {
        case STATE_TITLE:
            display_title();
            state = STATE_START;
            break;
        case STATE_START:
            start_game();
            state= STATE_TITLE;
            break;
        default:
            break;
        }
    }
}
