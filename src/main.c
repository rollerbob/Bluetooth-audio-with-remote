#include <avr/io.h>

int main (void)
{
	DDRD = 0xFF;
	uint8_t a=0;
	for (;;)
	{
		a++;
		PORTD = a;
	}
	return 0;
}