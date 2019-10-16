#ifndef SET_H
#define SET_H

#include <stdbool.h>

#include "navswitch.h"

#include "logos.h"

/**
 * Sets a char ROCK, PAPER or SCISSORS; its symbols defined above,
 * when navswitch is pushed north or south.
 * Returns the char to be set.
 */
char set_character (char character, bool sent);


/**
 * Called to set winner of game.
 * Returns an int result that determines the winner of the game.
 */
int set_winner(char outgoingCharacter, char incomingCharacter);

#endif
