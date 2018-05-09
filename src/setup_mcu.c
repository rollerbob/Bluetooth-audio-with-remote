#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include "hdr/setup_mcu.h"

void Setup_MCU(void){
//������ ���������� �� ����� �������������
    cli();
//��������� ������ �����/������
    DDRB = 0xFF;
    PORTB = 0x00;

//��������� ADC
    Init_ADC();

//��������� �������
    Init_timer(100);

//������ ���������� ���������
    sei();
}