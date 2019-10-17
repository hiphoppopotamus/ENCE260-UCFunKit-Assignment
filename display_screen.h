/** GROUP 307 ewi45 cjm356
    @file   display_screen.h
    @author Euan Widaja, Cam Maslin
    @date   16 October 2019
    @brief  Displays the desired images/text on the LED matrix screen.

    @note   Contains all functions associated with displaying
            required by the game.
*/


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
 * Then displays the string by passing it
 * as a parameter of tinygl_text.
 *
 * Function derived from 'lab3-ex2.c',
 * written by the ENCE260 team.
 *
 * @param character char to be displayed
 */
void display_character (char character);


/**
 * Displays the current score that current player has.
 * Calls passes its parameter score to display_character ()
 * for score displaying.
 *
 * @param score int to be displayed
 */
void display_score (int score);


/**
 * Displays a score bar utilising the ledmat module.
 * Takes a char score as a parameter to indicate a
 * score bar using tinygl_point().
 *
 * @param score char to indicate pixel coordinates
 */
void display_score_pixel (char score);


/**
 * Displays each round of the game, with a maximum of 9 rounds.
 * Takes an int round as a parameter and concatenates it with
 * the string "ROUND-". Resulting string then passed as a parameter of
 * tinygl_text. Called each time before the start of a round.
 *
 * @param round int indicates round of the game
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
 *
 * @param score int player's score
 * @param opponent_score int opponent's score
 */
void display_results_screen (int score, int opponent_score);


#endif
