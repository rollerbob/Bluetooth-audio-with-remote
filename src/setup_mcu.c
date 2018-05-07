#include <avr/io.h>
#include <avr/iom8.h>
#include "hdr/setup_mcu.h"

void Setup_MCU(void){
//Настройка портов ввода/вывода
    DDRB = 0xFF;
    PORTB = 0x00;

//Настройка ADC
    Init_ADC();

//Настройка таймера
    Init_timer(100);
}