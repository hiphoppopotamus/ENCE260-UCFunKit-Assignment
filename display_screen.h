#ifndef DISPLAY_TITLE_H
#define DISPLAY_TITLE_H

#define MESSAGE_RATE 20
#define RESULT_RATE 30

#include <string.h>

#include "tinygl.h"
#include "button.h"
#include "navswitch.h"
#include "io_init_update.h"

#include "fontPSRSideways.h"

/**
 * Displays the game's title screen
 * using the tinygl module and a predefined font
 * 'fontPSRSideways' that includes symbols for
 * a rock, paper, and scissors.
 */
void display_title (void);

/**
 * Takes a char character, creates a char array,
 * and inserts the character in.
 * Then displays the string with tinygl_text.
 *
 * Function derived from 'lab3-ex2.c',
 * written by the ENCE260 team.
 */
void display_character (char character);

/**
 * Displays the current score that current player has.
 */
void display_score (int score);

/**
 * Displays a score bar utilising the ledmat module.
 * Takes a char score as a parameter to indicate
 * the score bar.
 */
void display_score_pixel (char score);

/**
 * Displays each round of the game, with a maximum of 9 rounds.
 * Takes an int round as a parameter, and is called each time
 * before the start of a round.
 */
void display_round (int round);

/**
 * Takes an int score that indicates the player's score,
 * an int opponent_score that indicates the opponent's score,
 *
 * Displays the appropriate, overall results screen for the game:
 * If player's score is greater than opponent's, then player wins.
 * If opponent's score is greater than player's, opponent wins.
 * If the player's and the opponent's scores are equal, nobody wins.
 */
void display_results_screen (int score, int opponent_score);


#endif
