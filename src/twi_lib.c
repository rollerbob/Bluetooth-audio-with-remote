//ПЛАТФОРМОЗАВИСИМАЯ ЧАСТЬ

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "twi_lib.h"

//Используемые переменные
uint8_t *_msg;
uint8_t _msg_size;
volatile uint8_t twi_state = TWI_NO_STATE;

void Twi_init(void)
{
	//Установка скорости передачи
	TWBR = TWI_SPEED;
	TWSR = 0;
	TWCR = 1 << TWEN;
}


void Twi_send(uint8_t *msg, uint8_t msg_size)
{
	_msg = malloc(msg_size);
	uint8_t i;
	for (i = 0; i < msg_size; i++)
	{
		_msg[i] = msg[i];
	}
	_msg_size = msg_size;
	//Состояние TWI-модуля - занят
	twi_state = TWI_BUSY;

	//Запускаю передачу!
	TWCR = 1 << TWEN | 1 << TWIE | 1 << TWINT | 1 << TWSTA;
}

ISR (TWI_vect)
{
	static uint8_t i;
	uint8_t twi_status = TWSR & TWSR_MASK;

	switch (twi_status)
	{
		case TWI_START:
		case TWI_REP_START:
			i = 0;
			TWDR = LCD_ADDR;
			TWCR = 1 << TWINT | 1 << TWEN | 1 << TWIE;
		break;

		case TWI_MTX_ADR_ACK:
		case TWI_MTX_DATA_ACK:
			if (i < _msg_size)
			{
				TWDR = _msg[i++];
				TWCR = 1 << TWINT | 1 << TWEN | 1 << TWIE;
			} else 
			{
				twi_state = TWI_SUCCESS;
				free(_msg);
				TWCR = 1 << TWEN | 1 << TWINT | 1 << TWSTO | 0 << TWIE;
			}
		break;

		case TWI_MRX_DATA_ACK:
       		_msg[i++] = TWDR;
    
    	case TWI_MRX_ADR_ACK:
      		if (i < (_msg_size-1)){
        		TWCR = 1 << TWEN | 1 << TWIE | 1 << TWINT | 1 << TWEA;
      		}
      		else {
        		TWCR = 1 << TWEN | 1 << TWIE | 1 << TWINT;
      		}    
      	break; 
      
    	case TWI_MRX_DATA_NACK:
      		_msg[i] = TWDR;
      		twi_state = TWI_SUCCESS;  
      		TWCR = 1 << TWEN | 1 << TWINT | 1 << TWSTO;
      	break;
      	
      	case TWI_MTX_ADR_NACK:
	    case TWI_MRX_ADR_NACK:
    	case TWI_MTX_DATA_NACK:
    	case TWI_BUS_ERROR:
    	default:     
      		twi_state = twi_status;                                                                                    
      		TWCR = 1 << TWEN | 0 << TWIE | 0 << TWINT | 0<<TWEA | 0 << TWSTA | 0 << TWSTO | 0<<TWWC;
	}
}