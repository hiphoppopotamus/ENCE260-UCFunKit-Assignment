/** @file   game.c
    @author Euan Widaja, Cam Maslin
    @date   9 October 2019
    @brief  A simple rock, paper, scissors game with a maximum of
            9 rounds and a score board.

    @defgroup game A simple rock, paper, scissors game .
*/

#include "system.h"
#include "pacer.h"
#include "ledmat.h"
#include "tinygl.h"
#include "fonts/fontPSRSideways.h"
#include "navswitch.h"
#include "ir_uart.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "button.h"
#include "led.h"

#include "io_init_update.h"

#define LOOP_RATE 300
#define MESSAGE_RATE 20
#define PACER_RATE 500

#define ROCK '@'
#define PAPER '#'
#define SCISSORS '$'

void display_character (char character);
void display_score (int score);
void display_results_screen (int score, int opponent_score);

typedef enum {
    STATE_TITLE,
    STATE_START
} state_t;

/**
 * Called to set winner of game.
 * Returns an int result that determines the winner of the game.
 */
int winner(char outgoingCharacter, char incomingCharacter)
{
    int result = 0;
    if (outgoingCharacter == ROCK) {
        if (incomingCharacter == ROCK) {
            result = 0; // Draw
        } else if (incomingCharacter == PAPER) {
            result = 2; //player 2 (other) wins
        } else if (incomingCharacter == SCISSORS) {
            result = 1;
        }
    } else if (outgoingCharacter == PAPER) {
        if (incomingCharacter == PAPER) {
            result = 0;
        } else if (incomingCharacter == SCISSORS) {
            result = 2; //player 2 (other) wins
        } else if (incomingCharacter == ROCK) {
            result = 1;
        }
    } else if (outgoingCharacter == SCISSORS) {
        if (incomingCharacter == SCISSORS) {
            result = 0;
        } else if (incomingCharacter == ROCK) {
            result = 2; //player 2 (other) wins
        } else if (incomingCharacter == PAPER) {
            result = 1;
        }
    }
    return result;
}

/**
 * Sets a char ROCK, PAPER or SCISSORS; its symbols defined above,
 * when navswitch is pushed north or south.
 * Returns the char to be set.
 */
char set_character (char character, bool sent)
{
    if (navswitch_push_event_p(NAVSWITCH_NORTH) && sent == false) {
        if (character == ROCK) {
            character = SCISSORS;
        } else if (character == SCISSORS) {
            character = PAPER;
        } else if (character == PAPER) {
            character = ROCK;
        }
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && sent == false) {
        if (character == ROCK) {
            character = PAPER;
        } else if (character == PAPER) {
            character = SCISSORS;
        } else if (character == SCISSORS) {
            character = ROCK;
        }
    }
    return character;
}

/**
 * Displays a score bar utilising the ledmat module.
 * Takes a char score as a parameter to indicate
 * the score bar.
 */
void display_score_ledmat (char score)
{
    switch (score) {
    case '1':
        tinygl_pixel_set(tinygl_point(4, 0), 1);
        break;
    case '2':
        tinygl_pixel_set(tinygl_point(4, 0), 1);
        tinygl_pixel_set(tinygl_point(3, 0), 1);
        break;
    case '3':
        tinygl_pixel_set(tinygl_point(4, 0), 1);
        tinygl_pixel_set(tinygl_point(3, 0), 1);
        tinygl_pixel_set(tinygl_point(2, 0), 1);
        break;
    case '4':
        tinygl_pixel_set(tinygl_point(4, 0), 1);
        tinygl_pixel_set(tinygl_point(3, 0), 1);
        tinygl_pixel_set(tinygl_point(2, 0), 1);
        tinygl_pixel_set(tinygl_point(1, 0), 1);
        break;
    case '5':
        tinygl_pixel_set(tinygl_point(4, 0), 1);
        tinygl_pixel_set(tinygl_point(3, 0), 1);
        tinygl_pixel_set(tinygl_point(2, 0), 1);
        tinygl_pixel_set(tinygl_point(1, 0), 1);
        tinygl_pixel_set(tinygl_point(0, 0), 1);
        break;
    }
}

/**
 * Displays each round of the game, with a maximum of 9 rounds.
 * Takes an int round as a parameter, and is called each time
 * before the start of a round.
 */
void display_round (int round)
{
    char round_buff[2];
    round_buff[0] = round + '0';
    round_buff[1] = '\0';

    char buffer[8];
    strcpy (buffer, "ROUND-");
    strcat (buffer, round_buff);

    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text (buffer);


    while (1) {
        io_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            tinygl_clear();
            break;
        }
    }
}

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
    //ledmat_display_column (0x7c, 4);
    //ledmat_display_column (0x7c, 3);
    //ledmat_display_column (0x7c, 2);
    //ledmat_display_column (0x38, 1);
    //ledmat_display_column (0x00, 0);
    char incomingCharacter = ROCK;

    while (score != '6' && opponent_score != '6' && round < 10) {
        io_update ();
        display_round (round);
        tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
        while (1) {
            io_update ();
            character = set_character(character, sent);
            display_character (character);
            display_score_ledmat (score);
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
                won = winner(character, incomingCharacter);
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

/**
 * Displays the current score that current player has.
 */
void display_score (int score)
{
    while (1) {
        io_update();
        display_character(score);
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }
}

//FROM LAB FOR this function was written by some shit or modified by me to do shit
/**
 * Takes a char character, creates a char array,
 * and inserts the character in.
 * Then displays the string with tinygl_text.
 *
 * Function derived from 'lab3-ex2.c',
 * written by the ENCE260 team.
 */
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/**
 * Displays the game's title screen
 * using the tinygl module and a predefined font
 * 'fontPSRSideways' that includes symbols for
 * a rock, paper, and scissors.
 */
void display_title (void)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_font_set(&fontPSRSideways);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text("*ROCK@PAPER#SCISSORS$*");
    while (1) {
        io_update();
        if (button_push_event_p (0)) {
            tinygl_clear();
            break;
        }
    }
}

/**
 * Takes an int score that indicates the player's score,
 * an int opponent_score that indicates the opponent's score,
 *
 * Displays the appropriate, overall results screen for the game:
 * If player's score is greater than opponent's, then player wins.
 * If opponent's score is greater than player's, opponent wins.
 * If the player's and the opponent's scores are equal, nobody wins.
 */
void display_results_screen (int score, int opponent_score)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    if (score < opponent_score) {
        tinygl_text("@YOU#LOSER$");
    } else if (score > opponent_score) {
        tinygl_text("@YOU#WINNER$");
    } else if (score == opponent_score) {
        tinygl_text_speed_set(30);
        tinygl_text("$IT'S A DRAW$");
    }

    while (1) {
        io_update();
        if (button_push_event_p (0)) {
            tinygl_clear();
            break;
        }
    }
}

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
