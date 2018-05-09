// окюртнплнгюбхяхлюъ вюярэ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include "hdr/timer.h"

volatile uint8_t frame;

void Init_timer (uint8_t fps)
{
    frame = 0;
    TCCR2 = (1 << WGM21) | (1 << CS22);
    TIMSK = 1 << OCIE2;
    OCR2 = 50;
}

ISR (TIMER2_COMP_vect) {
    PORTB ^=1;
}