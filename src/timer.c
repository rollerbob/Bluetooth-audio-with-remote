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
}