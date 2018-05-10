//ПЛАТФОРМОЗАВИСИМАЯ ЧАСТЬ

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom8.h>
#include "hdr/adc_lib.h"

volatile uint8_t key1;
volatile uint8_t key2;

void Init_ADC(void){
    ADMUX = (1 << REFS0) | (1 << ADLAR) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADIF) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
}

uint8_t Get_key1(void) {
    return key1;
}

uint8_t Get_key2(void) {
    return key2;
}

ISR (ADC_vect) {
	uint8_t reg = ADMUX;
	if (reg & 0x01) key2 = ADCH;
		else key1 = ADCH;


//Запускаю новую конверсию
    ADMUX ^= 1 << MUX0;
    ADCSRA |= 1 << ADSC;
}