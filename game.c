#include "system.h"
#include "simplefont.h"
#include "pacer.h"
#include "ledmat.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 300

/* Define text update rate in Hz.  */
#define MESSAGE_RATE 2


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
        pacer_wait ();

        ledmat_display_column (font[(message[index] - ' ') * 5 + col],
                               col);

        col++;
        if (col > 4)
            col = 0;

        /* Advance message.  */
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


/*
# Link: create ELF output file from object files.
game.out: game.o system.o pio.o timer.o ledmat.o pacer.o
    $(CC) $(CFLAGS) $^ -o $@ -lm
    $(SIZE) $@

# Create hex file for programming from executable file.
game.hex: game.out
    $(OBJCOPY) -O ihex game.out game.hex


# Target: clean project.
.PHONY: clean
clean:
    -$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.hex
    dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start

*/
