// ПЛАТФОРМОЗАВИСИМАЯ ЧАСТЬ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include "timer.h"

volatile uint8_t frames_cntrs [] = {0,0};
volatile uint8_t secunds_cntrs [] = {0,0,0};

void Init_timer (void)
{
    uint8_t i;
    for (i = 0; i < sizeof(frames_cntrs); i++)
    {
        frames_cntrs [i] = 0;
    }
    for (i = 0; i < sizeof(secunds_cntrs); i++)
    {
        secunds_cntrs [i] = 0;
    }

    TCCR2 = (1 << WGM21) | (1 << CS22) | (1 << CS21) | (1 << CS20);
    TIMSK = 1 << OCIE2;
    OCR2 = FRAME_RATE;
}

void Pause_s (uint8_t secunds)
{
    secunds_cntrs [PAUSE_SECUNDS_CNTR] = 0;
    while (secunds_cntrs [PAUSE_SECUNDS_CNTR] != secunds);
}

ISR (TIMER2_COMP_vect) {
    uint8_t i;
    for (i = 0; i < sizeof (frames_cntrs); i++)
    {
        frames_cntrs [i] += 1;
    }

    if (frames_cntrs [SECUNDS_FRAME_CNTR] == 60)
    {
        frames_cntrs [SECUNDS_FRAME_CNTR] = 0;
        for (i = 0; i < sizeof (secunds_cntrs); i++)
        {
            secunds_cntrs [i] += 1;
        }
    }
}