#include <avr/io.h>
#include "setup_mcu.h"
#include "timer.h"
#include "buttons.h"

int main (void)
{
	Setup_MCU();

	for (;;)
	{
		Set_button(VOLUME_UP, ON);
	}
	return 0;
}