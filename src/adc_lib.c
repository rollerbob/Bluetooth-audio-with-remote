//ПЛАТФОРМОЗАВИСИМАЯ ЧАСТЬ

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom8.h>
#include "adc_lib.h"

volatile uint8_t key1 = 0;
volatile uint8_t key2 = 0;
volatile uint16_t key1_buff;
volatile uint16_t key2_buff;
volatile uint8_t adc1_cntr = 0;
volatile uint8_t adc2_cntr = 0;

void Init_ADC(void){
    ADMUX = (1 << REFS0) | (1 << ADLAR) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADIF) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
}

uint8_t Get_key(void) {
    if (key1 != 0xFF) return key1;
        else if (key2 != 0xFF) return key2;
    return 0xFF;
}

ISR (ADC_vect) {
	uint8_t reg = ADMUX;
    uint8_t adc_vol = ADCH;

    if (reg & 0x01)
    {
        if (adc_vol != 0xFF)
        {
            key2_buff += adc_vol;
            adc2_cntr++;

            if (adc2_cntr == 0xFF)
            {
                key2 = key2_buff / 256;
                key2_buff = 0;
            }
        } else
        {
            adc2_cntr = 0;
            key2_buff = 0;
            key2 = 0xFF;
        }
        
    } else
    {
         if (adc_vol != 0xFF)
        {
            key1_buff += adc_vol;
            adc1_cntr++;

            if (adc1_cntr == 0xFF)
            {
                key1 = key1_buff / 256;
                key1_buff = 0;
            }
        } else
        {
            adc1_cntr = 0;
            key1_buff = 0;
            key1 = 0xFF;
        }
    }
    
    
	
	

//Запускаю новую конверсию
    ADMUX ^= 1 << MUX0;
    ADCSRA |= 1 << ADSC;
}