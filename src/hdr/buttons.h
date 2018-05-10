#ifndef BUTTONS_H
#define BUTTONS_H

#define BUTTON_PORT_DDR 		DDRB
#define BUTTON_PORT 			PORTB

#define VOLUME_UP	0
#define VOLUME_DOWN 1
#define NEXT		2
#define PREV		3
#define PLAYPAUSE	4
#define MUTE		5
#define POWER		6

#define ON			1
#define	OFF			0

void Init_buttons(void);
void Set_button(uint8_t button, uint8_t state);

#endif