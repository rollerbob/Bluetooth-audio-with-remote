#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include "hdr/setup_mcu.h"
#include "hdr/buttons.h"
#include "hdr/timer.h"
#include "hdr/adc_lib.h"

void Setup_MCU(void){
//������ ���������� �� ����� �������������
    cli();
//��������� ������ �����/������ ������
    Init_buttons();

//��������� ADC
    Init_ADC();

//��������� �������
    Init_timer();

//������ ���������� ���������
    sei();
}