#ifndef TWI_LIB_H_INCLUDED
#define TWI_LIB_H_INCLUDED

#define TWI_SPEED       50000UL
#define TWBR_VALUE      (((F_CPU/TWI_SPEED)-16)/2)
#define TWSR_MASK		0xFC

#define BUFF_SIZE		9

#if ((TWBR_VALUE > 255) | (TWBR_VALUE == 0))
    #error "TWI init error"
#endif

/****************************************************************************
* Статусные коды модуля TWI
****************************************************************************/

/*Общие статусные коды */                    
#define TWI_START         			0x08  // состояние START сформировано 
#define TWI_REP_START     			0x10  // состояние повторный START сформировано 
#define TWI_ARB_LOST      			0x38  // был потерян приоритет 

/*Статусные коды ведущего передатчика*/                
#define TWI_MTX_ADR_ACK   			0x18  // был передан пакет SLA+W и получено подтверждение
#define TWI_MTX_ADR_NACK  			0x20  // был передан пает SLA+W и не получено подтверждение
#define TWI_MTX_DATA_ACK  			0x28  // был передан байт данных и получено подтверждение  
#define TWI_MTX_DATA_NACK 			0x30  // был передан байт данных и не получено подтверждение

/*Статусные коды ведущего приемника*/ 
#define TWI_MRX_ADR_ACK   			0x40  // был передан пакет SLA+R и получено подтвеждение 
#define TWI_MRX_ADR_NACK  			0x48  // был передан пакет SLA+R и не получено подтверждение 
#define TWI_MRX_DATA_ACK  			0x50  // байт данных принят и передано подтверждение  
#define TWI_MRX_DATA_NACK 			0x58  // был принят байт данных без подтверждения  

/*Другие статусные коды*/
#define TWI_NO_STATE      			0xF8  // неопределенное состояние; TWINT = “0”
#define TWI_BUSY					0xF7  // TWI модуль занят
#define TWI_BUS_ERROR     			0x00  // ошибка на шине из-за некоректных состояний СТАРТ или СТОП

/*Пользовательские коды*/
#define TWI_SUCCESS       			0xFF


/****************************************************************************
* Прототипы функций
****************************************************************************/
void Twi_init(void);
uint8_t twi_get_state(void);
void twi_send(uint8_t addr, uint8_t *msg, uint8_t msg_size);
void twi_get_data(uint8_t *msg, uint8_t msg_size);



#endif // TWI_LIB_H_INCLUDED
