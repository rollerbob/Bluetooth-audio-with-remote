#include <avr/io.h>
#include <util/delay.h>
#include "setup_mcu.h"
#include "timer.h"
#include "buttons.h"
#include "twi_lib.h"

int main (void)
{
	Setup_MCU();

	for (;;)
	{
		_delay_ms (500);
		PORTB = 0b10000000;
		_delay_ms (500);
		PORTB = 0;
	}
	return 0;
}