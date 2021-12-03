
#ifndef __ModbusSlave_H
#define __ModbusSlave_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"

	 
// ��������� ������������� ������
typedef struct
{
	uint8_t            *addr;     // ����� slave-����������
	uint16_t           *buf;      // ����� ������ �������
	uint16_t            bufLen;   // ������ ������ ������ �������
	UART_HandleTypeDef *uart;     // ����������������
	TIM_HandleTypeDef  *tim;      // ������ ���������� ������
	GPIO_TypeDef       *dirPort;  // ���� ������ ���������� RS485
	uint16_t            dirPin;   // ��� ������ ���������� RS485
	uint64_t           *gTick;    // ������ �� ������� ���������� �����
	uint16_t           *timeout;  // �������� �������� �����
} MBS_InitStruct;
	 
	 
// ������������� slave-���������
void MBS_Init(MBS_InitStruct *initStruct);
	 
// ���������� slave-���������
FuncRes MBS_Handler(void);
	 
// ���������� ���������� �� USATR (�����/��������)
void MBS_UART_Interrupt(void);
	 
// ���������� ���������� �� TIM (���������� ������)
void MBS_TIM_Interrupt(void);
	 

#ifdef __cplusplus
}
#endif
#endif
