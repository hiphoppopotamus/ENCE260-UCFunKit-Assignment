#include "system.h"
#include "pacer.h"
#include "ledmat.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "../fonts/fontPSR.h"
#include "navswitch.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 300

/* Define text update rate in Hz.  */
#define MESSAGE_RATE 20
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
    tinygl_text("RPS");
}

int set_start (int start)
{
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        if (start == 0) {
            tinygl_font_set(&font5x7_1);
            tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
            start = 1;
        } else if (start == 1) {
            display_title();
            start = 0;
        }
    }
    return start;
}

//JUST A TESTY
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


    char character = 'A';
    int start = 0;

    pacer_init (PACER_RATE);

    while (1) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update();

        start = set_start(start);            // Sets starts game or back to title screen

        if (start == 1) {
            tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
            /* Increment character if NORTH is pressed.  */
            if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
                character++;
            }

            /* Decrement character if SOUTH is pressed.  */
            if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
                character--;
            }

            display_character (character);
        }
    }
}



    /*
    int main (void)
    {
        char message[] = "ROCK PAPER SCISSORS";
        uint8_t col = 0;
        uint8_t index = 0;
        uint8_t tick = 0;

        system_init ();
        ledmat_init ();

        pacer_init (LOOP_RATE);


        while (1)
        {



            pacer_wait ();

            ledmat_display_column (font[(message[index] - ' ') * 5 + col],
                                   col);

            col++;
            if (col > 4)
                col = 0;



            tick++;
            if (tick >= LOOP_RATE / MESSAGE_RATE)
            {
                tick = 0;
                index++;
                if (!message[index])
                    index = 0;
            }
        }
    }

    */
