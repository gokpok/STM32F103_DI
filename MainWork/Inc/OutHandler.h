
#ifndef __OutHandler_H
#define __OutHandler_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
	 
// ��������� ����������� ������
typedef struct
{
	GPIO_TypeDef *port;         // ���� ����������� ������ (GPIOx)
	uint16_t      pin;          // ��� ����������� ������ (GPIO_PIN_x)
	uint64_t      changeTime;   // ����� ��������� ��������� ������
	uint16_t     *stateReg;     // ������� ���������� ����������
	uint16_t     *onCtrlReg;    // ������� �������� ���������
	uint16_t     *offCtrlReg;   // ������� �������� ����������
	uint16_t     *toCtrlReg;    // ������� �������� ��������
	uint16_t     *onErrReg;     // ������� ������ ���������
	uint16_t     *offErrReg;    // ������� ������ ����������
	uint8_t       bit;          // ����� ���� DO � ���������
} DO_StateStruct;
	 
	 
extern DO_StateStruct *DO_State;   // ��������� �� ������ ��������� �������������� DO
	 

// ������������� ������
void DO_Init(uint8_t num);
	 
// ���������� ������ � ������
void DO_Add(uint8_t num, GPIO_TypeDef *port, uint16_t pin, uint16_t *stateReg, uint16_t *onCtrlReg,
						uint16_t *offCtrlReg, uint16_t *toCtrlReg, uint16_t *onErrReg, uint16_t *offErrReg, uint8_t bit);

// ���������� ��������� DO
void DO_Handler(void);

#ifdef __cplusplus
}
#endif
#endif
