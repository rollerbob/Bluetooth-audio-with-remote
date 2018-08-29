#include <avr/io.h>
#include <avr/interrupt.h>
#include "twi_lib.h"

// Переменные
volatile static uint8_t buff[BUFF_SIZE];
volatile static uint8_t twi_msg_size;
volatile static uint8_t twi_state = TWI_NO_STATE;


/**
 * Инициализация модуля TWI
 */
void Twi_init(void)
{
    TWBR = TWBR_VALUE;
    TWSR = 0;
    TWCR = 1 << TWEN;
    twi_msg_size = 0;
}

/**
 * Возвращает текущее состояние модуля TWI
 * @return uint8_t  twi_state  состояние модуля TWI
 */
uint8_t twi_get_state(void)
{
	return twi_state;
}

void twi_send(uint8_t addr, uint8_t *msg, uint8_t msg_size)
{
	//Сохраняю длинну сообщения во внутреннюю переменную
	twi_msg_size = msg_size + 1;

	//Если нулевой бит первого байта массива установлен в 0, значит сообщение
	//нужно передать. 
	if (!(addr & 1)) {

	//Для этого я входной массив копирую во внутренний массив
		buff[0] = addr;
		int i;
		for (i = 0; i < msg_size; i++) buff[i+1] = msg[i];

	//Иначе я копирую адрес только в нулевой элемент внутреннего массива
	} else buff[0] = addr;

	//Состояние TWI-модуля - занят
	twi_state = TWI_BUSY;

	//Запускаю передачу!
	TWCR = 1 << TWEN | 1 << TWIE | 1 << TWINT | 1 << TWSTA;
}

void twi_get_data(uint8_t *msg, uint8_t msg_size)
{
	uint8_t i;
	for (i = 0; i<msg_size; i++)
	{
		msg[i] = buff[i+1];
	}
}

ISR (TWI_vect)
{
	static uint8_t i;
	uint8_t stat = TWSR & TWSR_MASK;

	switch (stat)
	{
		case TWI_START:
		case TWI_REP_START:
			i = 0;
			TWDR = buff[i++];
			TWCR = 1 << TWINT | 1 << TWEN | 1 << TWIE;
		break;

		case TWI_MTX_ADR_ACK:
		case TWI_MTX_DATA_ACK:
			if (i < twi_msg_size)
			{
				TWDR = buff[i];
				i++;
				TWCR = 1 << TWINT | 1 << TWEN | 1 << TWIE;
			} else 
			{
				twi_state = TWI_SUCCESS;
				TWCR = 1 << TWEN | 1 << TWINT | 1 << TWSTO | 0 << TWIE;
			}
		break;

		case TWI_MRX_DATA_ACK:
       		buff[i++] = TWDR;
    
    	case TWI_MRX_ADR_ACK:
      		if (i < (twi_msg_size-1)){
        		TWCR = 1 << TWEN | 1 << TWIE | 1 << TWINT | 1 << TWEA;
      		}
      		else {
        		TWCR = 1 << TWEN | 1 << TWIE | 1 << TWINT;
      		}    
      	break; 
      
    	case TWI_MRX_DATA_NACK:
      		buff[i] = TWDR;
      		twi_state = TWI_SUCCESS;  
      		TWCR = 1 << TWEN | 1 << TWINT | 1 << TWSTO;
      	break;
      	
      	case TWI_MTX_ADR_NACK:
	    case TWI_MRX_ADR_NACK:
    	case TWI_MTX_DATA_NACK:
    	case TWI_BUS_ERROR:
    	default:     
      		twi_state = stat;                                                                                    
      		TWCR = 1 << TWEN | 0 << TWIE | 0 << TWINT | 0<<TWEA | 0 << TWSTA | 0 << TWSTO | 0<<TWWC;
	}

}