
#ifndef __mbsData_H
#define __mbsData_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"


// ��������� ������
#define MBS_MAX_TRX_DATA 50
#define MBS_UART         USART3
#define MBS_TIM          TIM2

// ����������� ��� ���� ���������� RS485
#define MBS_DIR_ON     HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET)
#define MBS_DIR_OFF    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET)
	 
	 
// ������������ �������������� ������ ������
typedef enum
{
	MBS_FUNC_GET_REGS = 0x03,   // ��������� �������� ����� ���������
	MBS_FUNC_SET_REGS = 0x10,	  // ������� �������� ����� ���������
} MBS_FuncsEnum;

// ��������� ������ ��������� ������
typedef struct
{
	UART_HandleTypeDef *uart;     // ����������������
	TIM_HandleTypeDef  *tim;      // ������ ���������� ������
	GPIO_TypeDef       *dirPort;  // ���� ������ ���������� RS485
	uint16_t            dirPin;   // ��� ������ ���������� RS485
	uint64_t           *gTick;    // ������� ���������� �����
} MBS_PeripheryStruct;

// ��������� ���������� ���������� ������
typedef struct
{
	uint8_t  *addr;        // ����� save-����������
	uint16_t *timeout;     // �������� �������� �����
	uint8_t   endReciev;   // ���� ���������� ������
	uint16_t  dataBegin;   // ������ ������������� ������
	uint16_t  dataNum;     // ������ ������������� ������
	uint16_t  dataEnd;     // ����� ������������� ������
	uint16_t  rxLen;       // ������ ����������� ������
	uint16_t  txLen;       // ������ ������������� ������
	uint16_t  crc;         // ����������� �����
	uint16_t  count1;      // 1� ������� ����������� ����
	uint16_t  count2;      // 2� ������� ����������� ����
} MBS_VariablesStruct;


// ���������� ������ ������
extern volatile MBS_PeripheryStruct mbsPriph;                              // ���������
extern volatile MBS_VariablesStruct mbsVar;                                // ����������
extern          uint8_t             mbsRxBuf[MBS_MAX_TRX_DATA * 2 + 10];   // ����� ������
extern          uint8_t             mbsTxBuf[MBS_MAX_TRX_DATA * 2 + 10];   // ����� ��������
extern          uint16_t           *mbsBuf;                                // ����� ������ ������
extern          uint16_t            mbsBufLen;                             // ������ ������ ������ ������



#ifdef __cplusplus
}
#endif
#endif
