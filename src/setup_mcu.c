#include <avr/io.h>
#include <avr/iom8.h>
#include "hdr/setup_mcu.h"

void Setup_MCU(void){
    DDRB = 0xFF;
    PORTB = 0x00;
}