#include "system.h"
#include "pacer.h"
#include "ledmat.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "../fonts/fontPSR.h"
#include "navswitch.h"
#include "ir_uart.h"

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
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
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

void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

int main (void)
{
    system_init();
    tinygl_init(PACER_RATE);     // Loop Rate is the same as pacer rate
    display_title();             // Displays title screen
    navswitch_init();

    /*
        char sent_char = 'A';
        char received_char = 'A';
        int sent = 0;
        int received = 0;
    */

    char character = 'R';
    //char incomingCharacter = 'R';
    int start = 0;

    pacer_init (PACER_RATE);

    while (1) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update();

        start = set_start(start);            // Sets starts game or back to title screen

        if (start == 1) {
            tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);

/*
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                ir_uart_putc(character);
                //received = 0;
            }
*/

            /* Character received event */

/*
            if (ir_uart_read_ready_p()) {
                char char_buff = ir_uart_getc();
                if (char_buff >= 33 && char_buff <= 126) {
                    //received_char = char_buff;
                    //received = 1;
                }
            }
*/


            /* Increment character if NORTH is pressed.  */

            if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
                if (character == 'R') {
                    character = 'S';
                } else if (character == 'S') {
                    character = 'P';
                } else if (character == 'P') {
                    character = 'R';
                }
            }


            /* Decrement character if SOUTH is pressed.  */

            if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
                if (character == 'R') {
                    character = 'P';
                } else if (character == 'P') {
                    character = 'S';
                } else if (character == 'S') {
                    character = 'R';
                }
            }

            display_character (character);
        }
    }
}
