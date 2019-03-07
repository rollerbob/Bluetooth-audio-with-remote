#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include "setup_mcu.h"
#include "buttons.h"
#include "timer.h"
#include "adc_lib.h"
#include "ssd1306.h"

void Setup_MCU(void){
//Запрет прерываний на время инициализации
    cli();
//Настройка портов ввода/вывода кнопок
    Init_buttons();

//Настройка ADC
    Init_ADC();

//Настройка таймера
    Init_timer();

//Настройка UART
//  Init_UART();

//Настройка дисплея

//Теперь прерывания разрешены
    sei();
//    Init_lcd();
}