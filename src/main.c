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
		;
	}
	return 0;
}