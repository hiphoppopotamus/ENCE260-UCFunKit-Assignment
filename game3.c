#include "system.h"
#include "pacer.h"
#include "ledmat.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "../fonts/fontPSR.h"
#include "navswitch.h"
#include "ir_uart.h"
#include <avr/io.h>
#include "button.h"
#include "led.h"


#define ROCK_LOGO "*"

/* Define polling rate in Hz.  */
#define LOOP_RATE 300

/* Define text update rate in Hz.  */
#define MESSAGE_RATE 8
#define PACER_RATE 500


void display_title (void)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_font_set(&fontPSR);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text("RPS");
}

void blueLED(int on)
{
    if (on == 1) {
        led_set (LED1, 1);
    } else if (on == 0) {
        led_set (LED1, 0);
    }

    // led_set (LED1, on);
}

void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

int winner(char outgoingCharacter, char incomingCharacter)
{
    if (outgoingCharacter == 'R') {
        if (incomingCharacter == 'R') {
            return 0; // Draw
        } else if (incomingCharacter == 'P') {
            return 2; //player 2 (other) wins
        } else if (incomingCharacter == 'S') {
            return 1;
        }
    } else if (outgoingCharacter == 'P') {
        if (incomingCharacter == 'P') {
            return 0;
        } else if (incomingCharacter == 'S') {
            return 2; //player 2 (other) wins
        } else if (incomingCharacter == 'R') {
            return 1;
        }
    } else if (outgoingCharacter == 'S') {
        if (incomingCharacter == 'S') {
            return 0;
        } else if (incomingCharacter == 'R') {
            return 2; //player 2 (other) wins
        } else if (incomingCharacter == 'P') {
            return 1;
        }
    }
    return 0;
}


void initialise (void)
{
    system_init ();
    led_init ();                 // Initialises LED
    led_set (LED1, 0);
    button_init ();              // Initialises Button
    navswitch_init();
    ir_uart_init ();
    tinygl_init(PACER_RATE);     // Loop Rate is the same as pacer rate
    pacer_init (PACER_RATE);

}

void start_game (void)
{
    if (button_push_event_p (0)) {
        char score = '0';
        //int otherScore = 0;

        int sent = 0;
        int received = 0;

        char character = 'R';
        char incomingCharacter = 'R';

        while (1) {
            pacer_wait ();
            tinygl_update ();
            navswitch_update();
            button_update();
            //tinygl_font_set(&font5x7_1); // basic abcd font
            tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);

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

            display_character (character);

            if (received == 1 && sent == 1) {
                int won = winner(character, incomingCharacter);
                if (won == 1) {
                    score++;
                }
                display_character(score);
                received = 0;
                sent = 0;
                blueLED(0);
            }
        }
    }
}

int main (void)
{
    initialise();
    display_title();             // Displays title screen

    while (1) {
        pacer_wait ();
        tinygl_update ();
        //navswitch_update();
        button_update();
        start_game();            // Sets starts game or back to title screen
    }
}
