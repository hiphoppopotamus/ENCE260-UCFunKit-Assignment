/** GROUP 307 ewi45 cjm356
    @file   display_screen.c
    @author Euan Widaja, Cam Maslin
    @date   16 October 2019
    @brief  Displays the desired images/text on the LED matrix screen.

    @note   Contains all functions associated with displaying
            required by the game.
*/


#include "display_screen.h"


/**
 * Displays the game's title screen
 * using the tinygl module and a predefined font
 * 'fontPSRSideways' that includes symbols for
 * a rock, paper, and scissors.
 */
void display_title (void)
{
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_font_set (&fontPSRSideways);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text ("*ROCK@PAPER#SCISSORS$*");
    while (1) {
        io_update ();
        if (button_push_event_p (0)) {
            tinygl_clear ();
            break;
        }
    }
}


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
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


/**
 * Displays the current score that current player has.
 * Calls passes its parameter score to display_character ()
 * for score displaying.
 *
 * @param score int to be displayed
 */
void display_score (int score)
{
    while (1) {
        io_update ();
        display_character (score);
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            break;
        }
    }
}


/**
 * Displays a score bar utilising the ledmat module.
 * Takes a char score as a parameter to indicate a
 * score bar using tinygl_point().
 *
 * @param score char to indicate pixel coordinates
 */
void display_score_pixel (char score)
{
    switch (score) {
    case '1':
        tinygl_pixel_set (tinygl_point(4, 0), 1);
        break;
    case '2':
        tinygl_pixel_set (tinygl_point(4, 0), 1);
        tinygl_pixel_set (tinygl_point(3, 0), 1);
        break;
    case '3':
        tinygl_pixel_set (tinygl_point(4, 0), 1);
        tinygl_pixel_set (tinygl_point(3, 0), 1);
        tinygl_pixel_set (tinygl_point(2, 0), 1);
        break;
    case '4':
        tinygl_pixel_set (tinygl_point(4, 0), 1);
        tinygl_pixel_set (tinygl_point(3, 0), 1);
        tinygl_pixel_set (tinygl_point(2, 0), 1);
        tinygl_pixel_set (tinygl_point(1, 0), 1);
        break;
    case '5':
        tinygl_pixel_set (tinygl_point(4, 0), 1);
        tinygl_pixel_set (tinygl_point(3, 0), 1);
        tinygl_pixel_set (tinygl_point(2, 0), 1);
        tinygl_pixel_set (tinygl_point(1, 0), 1);
        tinygl_pixel_set (tinygl_point(0, 0), 1);
        break;
    }
}


/**
 * Displays each round of the game, with a maximum of 9 rounds.
 * Takes an int round as a parameter and concatenates it with
 * the string "ROUND-". Resulting string then passed as a parameter of
 * tinygl_text. Called each time before the start of a round.
 *
 * @param round int indicates round of the game
 */
void display_round (int round)
{
    char round_buff[2];
    round_buff[0] = round + '0';
    round_buff[1] = '\0';

    char buffer[8];
    strcpy (buffer, "ROUND-");
    strcat (buffer, round_buff);

    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text (buffer);
    while (1) {
        io_update ();
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            tinygl_clear ();
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
 *
 * @param score int player's score
 * @param opponent_score int opponent's score
 */
void display_results_screen (int score, int opponent_score)
{
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    if (score < opponent_score) {
        tinygl_text ("@YOU#LOSER$");
    } else if (score > opponent_score) {
        tinygl_text ("@YOU#WINNER$");
    } else if (score == opponent_score) {
        tinygl_text_speed_set (RESULT_RATE);
        tinygl_text ("$IT'S A DRAW$");
    }

    while (1) {
        io_update ();
        if (button_push_event_p (0)) {
            tinygl_clear ();
            break;
        }
    }
}
