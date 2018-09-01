#include <avr/io.h>
#include <util/delay.h>
#include "ssd1306.h"
#include "twi_lib.h"

#define DC_BIT						6
#define CONTROL_BYTE_COMMAND		0 << DC_BIT  
#define CONTROL_BYTE_DATA			1 << DC_BIT 

// Локальные функции
void Send_command(uint8_t command);
void Send_data(uint8_t data);

void Init_lcd(void)
{
	Twi_init();
	_delay_ms (500);
	Send_command(0xAE);
}

void Send_command (uint8_t command)
{
	uint8_t msg[] = {CONTROL_BYTE_COMMAND, command};
	Twi_send (msg, 2);
}