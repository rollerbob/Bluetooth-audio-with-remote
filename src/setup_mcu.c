#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include "hdr/setup_mcu.h"
#include "hdr/buttons.h"
#include "hdr/timer.h"
#include "hdr/adc_lib.h"

void Setup_MCU(void){
//Запрет прерываний на время инициализации
    cli();
//Настройка портов ввода/вывода кнопок
    Init_buttons();

//Настройка ADC
    Init_ADC();

//Настройка таймера
    Init_timer();

//Теперь прерывания разрешены
    sei();
}