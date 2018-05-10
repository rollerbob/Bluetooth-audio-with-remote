#include <avr/io.h>
#include "hdr/setup_mcu.h"
#include "hdr/timer.h"
#include "hdr/buttons.h"

int main (void)
{
	Setup_MCU();

	for (;;)
	{
		Set_button(VOLUME_UP, ON);
	}
	return 0;
}