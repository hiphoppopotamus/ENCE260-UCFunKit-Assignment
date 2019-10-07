#include "system.h"
#include "pacer.h"
#include "ledmat.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "../fonts/fontPSR.h"
#include "navswitch.h"
#include "ir_uart.h"
#include <avr/io.h>

#define ROCK_LOGO "*"

/* Define polling rate in Hz.  */
#define LOOP_RATE 300

/* Define text update rate in Hz.  */
#define MESSAGE_RATE 8
#define PACER_RATE 500


void display_title (void)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    /*
        tinygl_font_set(&font5x7_1);
        tinygl_text("ROCK ");
        tinygl_font_set(&fontPSR);
        tinygl_text("R ");
        tinygl_font_set(&font5x7_1);
        tinygl_text("PAPER ");
        tinygl_font_set(&fontPSR);
        tinygl_text("P ");
        tinygl_font_set(&font5x7_1);
        tinygl_text("SCISSORS ");
        tinygl_font_set(&fontPSR);
        tinygl_text("S ");
    */
    tinygl_font_set(&fontPSR);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text("RPS");
}

int set_start (int start)
{
    //if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
    if ((PIND & (1 << 7)) != 0) {
        if (start == 0) {
            //tinygl_font_set(&font5x7_1); // basic abcd font
            tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
            start = 1;
        }
        /*
                else if (start == 1) {
                    display_title();
                    start = 0;
                }
        */
    }
    return start;
}


void blueLED(int on)
{
    if (on == 1) {
        PORTC |= (1 << 2);
    } else if (on == 0) {
        PORTC &= ~(1 << 2);
    }
}


void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

int winner(char ownSelection, char otherSelection)
{
    if (ownSelection == 'R') {
        if (otherSelection == 'R') {
            return 0;
        } else if (otherSelection == 'P') {
            return 2; //player 2 (other) wins
        } else if (otherSelection == 'S') {
            return 1;
        }
    } else if (ownSelection == 'P') {
        if (otherSelection == 'P') {
            return 0;
        } else if (otherSelection == 'S') {
            return 2; //player 2 (other) wins
        } else if (otherSelection == 'R') {
            return 1;
        }
    } else if (ownSelection == 'S') {
        if (otherSelection == 'S') {
            return 0;
        } else if (otherSelection == 'R') {
            return 2; //player 2 (other) wins
        } else if (otherSelection == 'P') {
            return 1;
        }
    } else {
        return 0;
    }
}

int main (void)
{
    system_init();
    tinygl_init(PACER_RATE);     // Loop Rate is the same as pacer rate
    display_title();             // Displays title screen
    navswitch_init();
    DDRC |= (1 << 2);
    DDRD |= (0 << 7);

    ir_uart_init ();

    char score = '0';
    //int otherScore = 0;


    int sent = 0;
    int received = 0;

    char character = 'R';
    char incomingCharacter = 'R';
    int start = 0;

    pacer_init (PACER_RATE);

    while (1) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update();

        start = set_start(start);            // Sets starts game or back to title screen

        if (start == 1) {

            tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);

            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                ir_uart_putc(character);
                sent = 1;
            }

            /* Character received event */

            if (ir_uart_read_ready_p()) {
                char char_buff = ir_uart_getc();
                if (char_buff >= 33 && char_buff <= 126) {
                    incomingCharacter = char_buff;
                    received = 1;
                    blueLED(1);
                }
            }


            /* Increment character if NORTH is pressed.  */

            if (navswitch_push_event_p(NAVSWITCH_NORTH) && sent == 0) {
                if (character == 'R') {
                    character = 'S';
                } else if (character == 'S') {
                    character = 'P';
                } else if (character == 'P') {
                    character = 'R';
                }
            }


            /* Decrement character if SOUTH is pressed.  */

            if (navswitch_push_event_p(NAVSWITCH_SOUTH) && sent == 0) {
                if (character == 'R') {
                    character = 'P';
                } else if (character == 'P') {
                    character = 'S';
                } else if (character == 'S') {
                    character = 'R';
                }
            }

            display_character (character);
            if (received == 1 && sent == 1) {
                int won = winner(character, incomingCharacter);
                if (won == 1) {
                    score++;
                }
                display_character(score);
                received = 0;
                sent = 0;
                start = 0;
                blueLED(0);

            }


        }
    }
}
