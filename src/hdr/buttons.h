#ifndef BUTTONS_H
#define BUTTONS_H

#define BUTTON_PORT_DDR 		DDRB
#define BUTTON_PORT 			PORTB

#define VOLUME_UP_BTN		0
#define VOLUME_DOWN_BTN 	1
#define NEXT_BTN			2
#define PREV_BTN			3
#define PLAYPAUSE_BTN		4
#define MUTE_BTN			5
#define POWER_BTN			6

#define ON			1
#define	OFF			0

void Init_buttons(void);
void Set_button(uint8_t button, uint8_t state);
void Toggle_button(uint8_t button);
void All_buttons_off(void);

#endif