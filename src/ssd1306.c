#include <avr/io.h>
#include <avr/pgmspace.h>
#include "ssd1306.h"
#include "twi_lib.h"
#include "timer.h"

#define DC_BIT						6
#define CONTROL_BYTE_COMMAND		0 << DC_BIT  
#define CONTROL_BYTE_DATA			1 << DC_BIT 

//  ���������� �������
void Send_command(uint8_t command);
void Send_data(uint8_t data);

// ������� ������������� �������
const uint8_t init_codes[] PROGMEM = 
{
   	0xAE, // Set display OFF		
   	0xD4, // Set Display Clock Divide Ratio / OSC Frequency
   	0x80, // Display Clock Divide Ratio / OSC Frequency 
   	0xA8, // Set Multiplex Ratio
   	0x1F, // Multiplex Ratio for 128x64 (64-1) (0x1F 128x32)(0x3F 128x64)
   	0xD3, // Set Display Offset
   	0x00, // Display Offset
   	0x40, // Set Display Start Line
   	0x8D, // Set Charge Pump
   	0x14, // Charge Pump (0x10 External, 0x14 Internal DC/DC)
   	0xA1, // Set Segment Re-Map
   	0xC8, // Set Com Output Scan Direction
   	0xDA, // Set COM Hardware Configuration
   	0x02, // COM Hardware Configuration (0x02 128x32) (0x12 128x64)
   	0x81, // Set Contrast
   	0xCF, // Contrast
   	0xD9, // Set Pre-Charge Period
   	0xF1, // Set Pre-Charge Period (0x22 External, 0xF1 Internal)
   	0xDB, // Set VCOMH Deselect Level
   	0x40, // VCOMH Deselect Level
   	0xA4, // Set all pixels OFF
   	0xA6, // Set display not inverted
	0x20, // Set memory addressing mode
	0x00, // page addressing mode
   	0xAF  // Set display On
};

// ����� 5 � 7
const uint8_t font5x8 [] PROGMEM =
{
	0x00, 0x00, 0x00, 0x00, 0x00,// (space)
	0x00, 0x00, 0x5F, 0x00, 0x00,// !
	0x00, 0x07, 0x00, 0x07, 0x00,// "
	0x14, 0x7F, 0x14, 0x7F, 0x14,// #
	0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
	0x23, 0x13, 0x08, 0x64, 0x62,// %
	0x36, 0x49, 0x55, 0x22, 0x50,// &
	0x00, 0x05, 0x03, 0x00, 0x00,// '
	0x00, 0x1C, 0x22, 0x41, 0x00,// (
	0x00, 0x41, 0x22, 0x1C, 0x00,// )
	0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
	0x08, 0x08, 0x3E, 0x08, 0x08,// +
	0x00, 0x50, 0x30, 0x00, 0x00,// ,
	0x08, 0x08, 0x08, 0x08, 0x08,// -
	0x00, 0x60, 0x60, 0x00, 0x00,// .
	0x20, 0x10, 0x08, 0x04, 0x02,// /
	0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
	0x00, 0x42, 0x7F, 0x40, 0x00,// 1
	0x42, 0x61, 0x51, 0x49, 0x46,// 2
	0x21, 0x41, 0x45, 0x4B, 0x31,// 3
	0x18, 0x14, 0x12, 0x7F, 0x10,// 4
	0x27, 0x45, 0x45, 0x45, 0x39,// 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
	0x01, 0x71, 0x09, 0x05, 0x03,// 7
	0x36, 0x49, 0x49, 0x49, 0x36,// 8
	0x06, 0x49, 0x49, 0x29, 0x1E,// 9
	0x00, 0x36, 0x36, 0x00, 0x00,// :
	0x00, 0x56, 0x36, 0x00, 0x00,// ;
	0x00, 0x08, 0x14, 0x22, 0x41,// <
	0x14, 0x14, 0x14, 0x14, 0x14,// =
	0x41, 0x22, 0x14, 0x08, 0x00,// >
	0x02, 0x01, 0x51, 0x09, 0x06,// ?
	0x32, 0x49, 0x79, 0x41, 0x3E,// @
	0x7E, 0x11, 0x11, 0x11, 0x7E,// A
	0x7F, 0x49, 0x49, 0x49, 0x36,// B
	0x3E, 0x41, 0x41, 0x41, 0x22,// C
	0x7F, 0x41, 0x41, 0x22, 0x1C,// D
	0x7F, 0x49, 0x49, 0x49, 0x41,// E
	0x7F, 0x09, 0x09, 0x01, 0x01,// F
	0x3E, 0x41, 0x41, 0x51, 0x32,// G
	0x7F, 0x08, 0x08, 0x08, 0x7F,// H
	0x00, 0x41, 0x7F, 0x41, 0x00,// I
	0x20, 0x40, 0x41, 0x3F, 0x01,// J
	0x7F, 0x08, 0x14, 0x22, 0x41,// K
	0x7F, 0x40, 0x40, 0x40, 0x40,// L
	0x7F, 0x02, 0x04, 0x02, 0x7F,// M
	0x7F, 0x04, 0x08, 0x10, 0x7F,// N
	0x3E, 0x41, 0x41, 0x41, 0x3E,// O
	0x7F, 0x09, 0x09, 0x09, 0x06,// P
	0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
	0x7F, 0x09, 0x19, 0x29, 0x46,// R
	0x46, 0x49, 0x49, 0x49, 0x31,// S
	0x01, 0x01, 0x7F, 0x01, 0x01,// T
	0x3F, 0x40, 0x40, 0x40, 0x3F,// U
	0x1F, 0x20, 0x40, 0x20, 0x1F,// V
	0x7F, 0x20, 0x18, 0x20, 0x7F,// W
	0x63, 0x14, 0x08, 0x14, 0x63,// X
	0x03, 0x04, 0x78, 0x04, 0x03,// Y
	0x61, 0x51, 0x49, 0x45, 0x43,// Z
	0x00, 0x00, 0x7F, 0x41, 0x41,// [
	0x02, 0x04, 0x08, 0x10, 0x20,// "\"
	0x41, 0x41, 0x7F, 0x00, 0x00,// ]
	0x04, 0x02, 0x01, 0x02, 0x04,// ^
	0x40, 0x40, 0x40, 0x40, 0x40,// _
	0x00, 0x01, 0x02, 0x04, 0x00,// `
	0x20, 0x54, 0x54, 0x54, 0x78,// a
	0x7F, 0x48, 0x44, 0x44, 0x38,// b
	0x38, 0x44, 0x44, 0x44, 0x20,// c
	0x38, 0x44, 0x44, 0x48, 0x7F,// d
	0x38, 0x54, 0x54, 0x54, 0x18,// e
	0x08, 0x7E, 0x09, 0x01, 0x02,// f
	0x08, 0x14, 0x54, 0x54, 0x3C,// g
	0x7F, 0x08, 0x04, 0x04, 0x78,// h
	0x00, 0x44, 0x7D, 0x40, 0x00,// i
	0x20, 0x40, 0x44, 0x3D, 0x00,// j
	0x00, 0x7F, 0x10, 0x28, 0x44,// k
	0x00, 0x41, 0x7F, 0x40, 0x00,// l
	0x7C, 0x04, 0x18, 0x04, 0x78,// m
	0x7C, 0x08, 0x04, 0x04, 0x78,// n
	0x38, 0x44, 0x44, 0x44, 0x38,// o
	0x7C, 0x14, 0x14, 0x14, 0x08,// p
	0x08, 0x14, 0x14, 0x18, 0x7C,// q
	0x7C, 0x08, 0x04, 0x04, 0x08,// r
	0x48, 0x54, 0x54, 0x54, 0x20,// s
	0x04, 0x3F, 0x44, 0x40, 0x20,// t
	0x3C, 0x40, 0x40, 0x20, 0x7C,// u
	0x1C, 0x20, 0x40, 0x20, 0x1C,// v
	0x3C, 0x40, 0x30, 0x40, 0x3C,// w
	0x44, 0x28, 0x10, 0x28, 0x44,// x
	0x0C, 0x50, 0x50, 0x50, 0x3C,// y
	0x44, 0x64, 0x54, 0x4C, 0x44,// z
	0x00, 0x08, 0x36, 0x41, 0x00,// {
	0x00, 0x00, 0x7F, 0x00, 0x00,// |
	0x00, 0x41, 0x36, 0x08, 0x00,// }
	0x08, 0x08, 0x2A, 0x1C, 0x08,// ->
	0x08, 0x1C, 0x2A, 0x08, 0x08 // <-
};

// ���������� ����������
char screen_buff[84];

void Init_lcd(void)
{
	Twi_init();

	Pause_s (2);

	uint8_t i = 0;

	uint8_t arr_size = sizeof (init_codes);
	while (i < arr_size)
	{
		Send_command(pgm_read_byte(&init_codes[i]));
		i++;
	}

	LCD_cls ();
	LCD_clear_screen_buff();
}

void Update_lcd ()
{
	if (Get_frames (LCD_REFRESH_CNTR) == 16)
	{
		Reset_cntr(FRAME_COUNTER, LCD_REFRESH_CNTR);
		LCD_cls();
		uint8_t i;
		for (i = 0; i < 84; i++)
		{
			uint8_t ch = screen_buff[i];
			if (!ch)
				ch = 0x20;
			LCD_print_char(ch);
		}
	}
}

void Send_command (uint8_t command)
{
	while (Get_twi_status() == TWI_BUSY);
	uint8_t msg[] = {CONTROL_BYTE_COMMAND, command};
	Twi_send (msg, 2);
}

void Send_data (uint8_t data)
{
	while (Get_twi_status() == TWI_BUSY);
	uint8_t msg[] = {CONTROL_BYTE_DATA, data};
	Twi_send (msg, 2);
}

void LCD_cls (void)
{
	LCD_Set_pos (0,0);
	uint16_t i = 0;
	while (i != 128*4)
	{
		Send_data (0x00);
		i++;
	}
	LCD_Set_pos (0,0);
}

void LCD_clear_screen_buff(void)
{
	uint8_t i;
	for (i = 0; i < 84; i++)
		screen_buff[i] = 0;
}

void LCD_Set_pos (uint8_t x, uint8_t y)
{
	Send_command (0x21);
	Send_command (x * 6);
	Send_command (0x7F);

	Send_command (0x22);
	Send_command (y);
	Send_command (0x03);
}

void LCD_print_char(char c)
{
	c -= 0x20;
	uint16_t font_index = c * 5;
	uint8_t i;
	for (i = 0; i < 5; i++)
	{
		Send_data (pgm_read_byte(&font5x8[font_index+i]));
	}
	Send_data(0x00);
}

void LCD_print_str (uint8_t clm, uint8_t lin, char *str)
{
	uint8_t index = lin * 21 + clm;
	while (*str)
	{
		screen_buff[index] = *str;
		str++;
		index++;
		if (index > 84)
			index = 0;
	}
}

void LCD_print_hex (uint8_t b)
{
	uint8_t low  = b & 0x0F;
	uint8_t high = (b & 0xF0) >> 4;

	uint8_t offset_l = (low > 0x09) ? 0x37:0x30;
	uint8_t offset_h = (high > 0x09) ? 0x37:0x30;

	LCD_print_char (offset_h + high);
	Send_data(0x00);
	LCD_print_char (offset_l + low);
	Send_data(0x00);
}