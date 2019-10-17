/** GROUP 307 ewi45 cjm356
    @file   set.c
    @author Euan Widaja, Cam Maslin
    @date   16 October 2019
    @brief  Set user options of characters to display
            and winners for each round

    @note   Includes functions to change characters between
            ROCK, PAPER, SCISSORS and to set winner of each round
*/


#include "set.h"


/**
 * Sets a char ROCK, PAPER or SCISSORS; its symbols defined above,
 * when navswitch is pushed north or south.
 * Returns the char to be set.
 *
 * @param character char to be set
 * @param sent boolean indicating if character has been sent
 * @return character to be displayed
 */
char set_character (char character, bool sent)
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH) && sent == false) {
        if (character == ROCK) {
            character = SCISSORS;
        } else if (character == SCISSORS) {
            character = PAPER;
        } else if (character == PAPER) {
            character = ROCK;
        }
    }

    if (navswitch_push_event_p (NAVSWITCH_SOUTH) && sent == false) {
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
 * Called to set winner of game.
 * Returns an int result that determines the winner of the round.
 * 0 if its a draw, 1 if you win and 2 if the other player wins.
 *
 * @param player_character char of player
 * @param opponent_character char of opponent
 * @return result int indicates winner of game
 */
int set_winner(char player_character, char opponent_character)
{
    int result = 0;
    if (player_character == ROCK) {
        if (opponent_character == ROCK) {
            result = 0; // Draw
        } else if (opponent_character == PAPER) {
            result = 2; // Opponent wins
        } else if (opponent_character == SCISSORS) {
            result = 1; // Player wins
        }
    } else if (player_character == PAPER) {
        if (opponent_character == PAPER) {
            result = 0;
        } else if (opponent_character == SCISSORS) {
            result = 2;
        } else if (opponent_character == ROCK) {
            result = 1;
        }
    } else if (player_character == SCISSORS) {
        if (opponent_character == SCISSORS) {
            result = 0;
        } else if (opponent_character == ROCK) {
            result = 2;
        } else if (opponent_character == PAPER) {
            result = 1;
        }
    }
    return result;
}
