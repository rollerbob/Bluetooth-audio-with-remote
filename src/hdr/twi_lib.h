#ifndef		TWI_LIB_H
#define		TWI_LIB_H

#define LCD_ADDR	0x7A // 0x7A|0x78
#define TWSR_MASK	0b11111000
//��������� �������� ��������
//TWBR = ((F_cpu/F_scl) - 16)/(2*4^TWPS)
#define TWI_SCL		400000UL
#define TWI_SPEED	((F_CPU/TWI_SCL) - 16) / 2

#if ((TWI_SPEED > 255) | (TWI_SPEED == 0))
    #error "TWI init error"
#endif

/*******************************************************************************
* ��������� ���� ������ TWI
*******************************************************************************/

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

// ������ ������ ��� ��������
#define TWI_BUFF_SIZE				16

/*******************************************************************************
* ��������� �������
*******************************************************************************/
void Twi_init(void);
void Twi_send(uint8_t *msg, uint8_t msg_size);
uint8_t Get_twi_status(void);

#endif