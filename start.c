/** GROUP 307 ewi45 cjm356
    @file   start.c
    @author Euan Widaja, Cam Maslin
    @date   16 October 2019
    @brief  Starts game of Rock Papers Scissors
*/


#include "start.h"


/**
 * Key function that starts game.
 *
 * Calls a function display_round () that starts each round.
 * Runs through each round until both players have selected an option.
 * Updates and displays the scoreboard based on the outcome of that round.
 * Repeats the above process, until either score is 6,
 * or round exceeds the maximum possible round (10).
 */
void start_game (void)
{
    char score = '0';
    char opponent_score = '0';

    int round = 1;
    int won = 0;

    bool sent = false;
    bool received = false;

    char character = ROCK;
    char incomingCharacter = ROCK;

    while (score != '6' && opponent_score != '6' && round < 10) {
        io_update ();
        display_round (round);
        tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
        while (1) {
            io_update ();
            character = set_character (character, sent);
            display_character (character);
            display_score_pixel (score);
            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                ir_uart_putc (character);
                sent = true;
            }
            if (ir_uart_read_ready_p ()) {
                char char_buff = ir_uart_getc ();
                if (char_buff == ROCK || char_buff == PAPER || char_buff == SCISSORS) {
                    incomingCharacter = char_buff;
                    received = true;
                    led_set (LED1, 1);
                }
            }
            // Decides the winner at the end of each round and updates score
            if (received == true && sent == true) {
                tinygl_clear ();
                led_set (LED1, 0);
                won = set_winner (character, incomingCharacter);
                if (won == 1) {
                    score++;
                } else if (won == 2) {
                    opponent_score++;
                }
                display_score (score);
                received = false;
                sent = false;
                round++;
                break;
            }
        }
    }
    display_results_screen (score, opponent_score);
}
