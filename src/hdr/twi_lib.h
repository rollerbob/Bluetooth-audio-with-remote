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
* ��������� ���� ������ TWI
****************************************************************************/

/*����� ��������� ���� */                    
#define TWI_START         			0x08  // ��������� START ������������ 
#define TWI_REP_START     			0x10  // ��������� ��������� START ������������ 
#define TWI_ARB_LOST      			0x38  // ��� ������� ��������� 

/*��������� ���� �������� �����������*/                
#define TWI_MTX_ADR_ACK   			0x18  // ��� ������� ����� SLA+W � �������� �������������
#define TWI_MTX_ADR_NACK  			0x20  // ��� ������� ���� SLA+W � �� �������� �������������
#define TWI_MTX_DATA_ACK  			0x28  // ��� ������� ���� ������ � �������� �������������  
#define TWI_MTX_DATA_NACK 			0x30  // ��� ������� ���� ������ � �� �������� �������������

/*��������� ���� �������� ���������*/ 
#define TWI_MRX_ADR_ACK   			0x40  // ��� ������� ����� SLA+R � �������� ������������ 
#define TWI_MRX_ADR_NACK  			0x48  // ��� ������� ����� SLA+R � �� �������� ������������� 
#define TWI_MRX_DATA_ACK  			0x50  // ���� ������ ������ � �������� �������������  
#define TWI_MRX_DATA_NACK 			0x58  // ��� ������ ���� ������ ��� �������������  

/*������ ��������� ����*/
#define TWI_NO_STATE      			0xF8  // �������������� ���������; TWINT = �0�
#define TWI_BUSY					0xF7  // TWI ������ �����
#define TWI_BUS_ERROR     			0x00  // ������ �� ���� ��-�� ����������� ��������� ����� ��� ����

/*���������������� ����*/
#define TWI_SUCCESS       			0xFF


/****************************************************************************
* ��������� �������
****************************************************************************/
void Twi_init(void);
uint8_t twi_get_state(void);
void twi_send(uint8_t addr, uint8_t *msg, uint8_t msg_size);
void twi_get_data(uint8_t *msg, uint8_t msg_size);



#endif // TWI_LIB_H_INCLUDED
