#include "system.h"
#include "pacer.h"
#include "ledmat.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "fonts/fontPSR.h"
#include "fonts/fontPSRSideways.h"
#include "navswitch.h"
#include "ir_uart.h"
#include <avr/io.h>
#include <stdbool.h>
#include "button.h"
#include "led.h"

#define LOOP_RATE 300
#define MESSAGE_RATE 20
#define PACER_RATE 500

#define ROCK '@'
#define PAPER '#'
#define SCISSORS '$'

typedef enum {
    STATE_TITLE,
    STATE_START
} state_t;

void initialise (void)
{
    system_init ();
    led_init ();
    button_init ();
    navswitch_init();
    ir_uart_init ();
    tinygl_init(PACER_RATE);
    pacer_init (PACER_RATE);
    led_set (LED1, 0);
}

void io_update (void)
{
    pacer_wait ();
    tinygl_update ();
    navswitch_update();
    button_update();

}

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

void start_game (void)
{

    char score = '0';
    //int otherScore = 0;

    bool sent = false;
    bool received = false;

    char character = ROCK;
    char incomingCharacter = ROCK;

    while (1) {
        io_update();
        tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
        character = set_character(character, sent);
        display_character (character);

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
            led_set (LED1, 0);
            int won = winner(character, incomingCharacter);
            if (won == 1) {
                score++;
            }
            display_score(score);
            received = false;
            sent = false;
        }
    }
}


//FROM LAB FOR this function was written by some shit or modified by me to do shit
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

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

void display_title (void)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_font_set(&fontPSRSideways);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text("*ROCK@*PAPER#*SCISSORS$*");
    while (1) {
        //ledmat_init();
        io_update();
        if (button_push_event_p (0)) {
            tinygl_clear();
            break;
        }
    }
}

int main (void)
{
    initialise();
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
