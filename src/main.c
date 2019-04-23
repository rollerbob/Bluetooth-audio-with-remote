#include <avr/io.h>
#include <util/delay.h>
#include "main.h"
#include "setup_mcu.h"
#include "timer.h"
#include "buttons.h"
#include "twi_lib.h"
#include "ssd1306.h"
#include "adc_lib.h"

// Внутренние функции
uint8_t Parse_cmd (uint8_t chnl);

// Глобальные переменные
uint8_t cmd = NONE_CMD;
uint8_t toggle = 0;

int main (void)
{
	Setup_MCU();

	LCD_print_str (0, 0, "Key = ");
	LCD_print_str (0, 1, "Cmd = ");

	for (;;)
	{
		Update_lcd();

		uint8_t key = Get_key();
		cmd = Parse_cmd(key);
		LCD_Set_pos(6,0);
		LCD_print_hex(0xFF);
		LCD_Set_pos(6,1);
		LCD_print_hex(0x15);
		switch (cmd)
		{
			case MODE_CMD:
				if (!toggle)
				{
					Toggle_button(POWER_BTN);
					toggle = 1;
				}
				break;

			case VOL_UP_CMD:
				Set_button (VOLUME_UP_BTN, ON);
				break;

			case VOL_DOWN_CMD:
				Set_button (VOLUME_DOWN_BTN, ON);
				break;

			case NEXT_CMD:
				Set_button (NEXT_BTN, ON);
				break;
			
			case PREV_CMD:
				Set_button (PREV_BTN, ON);
				break;

			case MUTE_CMD:
				Set_button (MUTE_BTN, ON);
				break;

			case HANDS_UP_CMD:
				Set_button (PLAYPAUSE_BTN, ON);
				break;

			default:
				toggle = 0;
				PORTB &= 0b11000000;
			break;
		}
	}

	return 0;
}

uint8_t Parse_cmd (uint8_t raw)
{
	uint8_t ret = 0;
	if (raw < 0x67 && raw > 0x64)
		ret = HANDS_UP_CMD;
	if (raw < 0x25 && raw > 0x22)
		ret = HANDS_DOWN_CMD;
	if (raw < 0x81 && raw > 0x7E)
		ret = GPS_CMD;
	if (raw < 0x9A && raw > 0x96)
		ret = BAND_CMD;
	if (raw < 0x48 && raw > 0x44)
		ret = MODE_CMD;
	if (raw < 0x53 && raw > 0x4F)
		ret = VOL_UP_CMD;
	if (raw < 0x07 && raw > 0x04)
		ret = VOL_DOWN_CMD;
	if (raw < 0x71 && raw > 0x6C)
		ret = NEXT_CMD;
	if (raw < 0x8D && raw > 0x88)
		ret = PREV_CMD;
	if (raw < 0x2F && raw > 0x2A)
		ret = MUTE_CMD;

	return ret;	
}