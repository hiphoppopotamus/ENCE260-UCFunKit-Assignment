#include "system.h"
#include "simplefont.h"
#include "pacer.h"
#include "ledmat.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 300

/* Define text update rate in Hz.  */
#define MESSAGE_RATE 30
#define PACER_RATE 500


void display_title (void)
{
    tinygl_init(PACER_RATE);     // Loop Rate is the same as pacer rate
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("PAPER SCISSORS ROCK");
}


int main (void)
{
    system_init();
    display_title();

    /* Set the message using tinygl_text().  */


    pacer_init (PACER_RATE);

    while (1) {
        pacer_wait();

        /* Call the tinygl update function. */
        tinygl_update();


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
        /* Wait for next tick.  */

/*
        pacer_wait ();

        ledmat_display_column (font[(message[index] - ' ') * 5 + col],
                               col);

        col++;
        if (col > 4)
            col = 0;

        /* Advance message.  */
/*
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
