// ПЛАТФОРМОЗАВИСИМАЯ ЧАСТЬ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include "timer.h"

volatile uint8_t frame;

void Init_timer (void)
{
    frame = 0;
    TCCR2 = (1 << WGM21) | (1 << CS22);
    TIMSK = 1 << OCIE2;
    OCR2 = FRAME_RATE;
}

uint8_t Get_frame(void)
{
	return frame;
}

ISR (TIMER2_COMP_vect) {
    frame++;
}