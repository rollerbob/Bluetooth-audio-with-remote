// ÏËÀÒÔÎĞÌÎÇÀÂÈÑÈÌÀß ×ÀÑÒÜ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom8.h>
#include "hdr/adc_lib.h"

volatile uint8_t key1;
volatile uint8_t key2;

void Init_ADC(void){
    ;
}

uint8_t Get_key1(void) {
    return key1;
}

uint8_t Get_key2(void) {
    return key2;
}