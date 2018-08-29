#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include "setup_mcu.h"
#include "buttons.h"
#include "timer.h"
#include "adc_lib.h"
#include "ssd1306.h"

void Setup_MCU(void){
//������ ���������� �� ����� �������������
    cli();
//��������� ������ �����/������ ������
    Init_buttons();

//��������� ADC
    Init_ADC();

//��������� �������
    Init_timer();

//��������� UART
//  Init_UART();

//��������� �������
    Init_lcd();

//������ ���������� ���������
    sei();
}