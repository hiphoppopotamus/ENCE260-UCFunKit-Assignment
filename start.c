/** GROUP 307 ewi45 cjm356
    @file   start.c
    @author Euan Widaja, Cam Maslin
    @date   16 October 2019
    @brief  Function that starts each round when the navswitch is pressed down.
    Also runs through each round until both players have selected an option and
    updates and displays the scoreboard depending on the outcome of that round.
*/


#include "start.h"

/**
 * Key function that starts game.
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
        tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
        while (1) {
            io_update ();
            character = set_character(character, sent);
            display_character (character);
            display_score_pixel (score);
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                ir_uart_putc(character);
                sent = true;
            }
            if (ir_uart_read_ready_p()) {
                char char_buff = ir_uart_getc();
                if (char_buff == ROCK || char_buff == PAPER || char_buff == SCISSORS) {
                    incomingCharacter = char_buff;
                    received = true;
                    led_set (LED1, 1);
                }
            }
            if (received == true && sent == true) {
                tinygl_clear();
                led_set (LED1, 0);
                won = set_winner(character, incomingCharacter);
                if (won == 1) {
                    score++;
                } else if (won == 2) {
                    opponent_score++;
                }
                display_score(score);
                received = false;
                sent = false;
                round++;
                break;
            }
        }
    }
    display_results_screen (score, opponent_score);
}
