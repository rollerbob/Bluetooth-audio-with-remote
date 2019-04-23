// ПЛАТФОРМОЗАВИСИМАЯ ЧАСТЬ 
#include <avr/io.h>
#include <avr/iom8.h>
#include "buttons.h"


void Init_buttons(void)
{
	BUTTON_PORT_DDR = 0xFF;
	BUTTON_PORT = 0x00;
}

void Set_button(uint8_t button, uint8_t state)
{
	if (state) BUTTON_PORT |= (1 << button);
		else BUTTON_PORT &= ~(1 << button);
}

void All_buttons_off(void)
{
	BUTTON_PORT = 0x00;
}

void Toggle_button (uint8_t button)
{
	BUTTON_PORT ^= 1 << button;
}