/** GROUP 307 ewi45 cjm356
    @file   set.c
    @author Euan Widaja, Cam Maslin
    @date   16 October 2019
    @brief  Functions to change the user options during each round and includes
    a function to decide the winner of each round.
*/


#include "set.h"


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
 * Called to set winner of game.
 * Returns an int result that determines the winner of the round.
 * 0 if its a draw, 1 if you win and 2 if the other player wins.
 */
int set_winner(char outgoingCharacter, char incomingCharacter)
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