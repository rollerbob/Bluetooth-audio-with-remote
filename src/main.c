#include "hdr/setup_mcu.h"

int main (void)
{
	Setup_MCU();
	unsigned short int a = 0;
	for (;;)
	{
		a++;
	}
	return 0;
}