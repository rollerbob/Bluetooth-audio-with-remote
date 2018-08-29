#include <avr/io.h>
#include "ssd1306.h"
#include "twi_lib.h"

void Init_lcd(void)
{
	Twi_init();
	twi_send(SSD1306_ADDR, )
}