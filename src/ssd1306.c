#include <avr/io.h>
#include <avr/pgmspace.h>
#include "ssd1306.h"
#include "twi_lib.h"

#define DC_BIT						6
#define CONTROL_BYTE_COMMAND		0 << DC_BIT  
#define CONTROL_BYTE_DATA			1 << DC_BIT 

// Локальные функции
void Send_command(uint8_t command);
void Send_data(uint8_t data);

// Локальные переменные
uint8_t init_codes[] PROGMEM = 
{
   	0xAE, // Set display OFF		
 //  	0xD4, // Set Display Clock Divide Ratio / OSC Frequency
 //  	0x80, // Display Clock Divide Ratio / OSC Frequency 
   	0xA8, // Set Multiplex Ratio
   	0x3F, // Multiplex Ratio for 128x64 (64-1)
   	0xD3, // Set Display Offset
   	0x00, // Display Offset
   	0x40, // Set Display Start Line
   	0x8D, // Set Charge Pump
   	0x14, // Charge Pump (0x10 External, 0x14 Internal DC/DC)
   	0xA1, // Set Segment Re-Map
   	0xC8, // Set Com Output Scan Direction
   	0xDA, // Set COM Hardware Configuration
   	0x12, // COM Hardware Configuration
   	0x81, // Set Contrast
   	0xCF, // Contrast
   	0xD9, // Set Pre-Charge Period
   	0xF1, // Set Pre-Charge Period (0x22 External, 0xF1 Internal)
   	0xDB, // Set VCOMH Deselect Level
   	0x40, // VCOMH Deselect Level
   	0xA4, // Set all pixels OFF
   	0xA6, // Set display not inverted
   	0xAF  // Set display On
};

void Init_lcd(void)
{
	Twi_init();

	uint8_t i = 0;
	uint8_t *c = init_codes;
	while (i < 21)
	{
		if (Get_twi_status() != TWI_BUSY) 
		{
			Send_command(pgm_read_byte(c));
			c++;
			i++;
		}
	}
	i = 0;
	while (i < 17)
	{
		if (Get_twi_status() != TWI_BUSY)
		{
			Send_data (i);
			i++;
		}
	}
}

void Send_command (uint8_t command)
{
	uint8_t msg[] = {CONTROL_BYTE_COMMAND, command};
	Twi_send (msg, 2);
}

void Send_data (uint8_t data)
{
	uint8_t msg[] = {CONTROL_BYTE_DATA, data};
	Twi_send (msg, 2);
}