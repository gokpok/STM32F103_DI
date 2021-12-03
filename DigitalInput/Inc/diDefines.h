
#ifndef __diDefines_H
#define __diDefines_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "DigitInput.h"
	 
	 
// ��������� �������� ����������� �����
typedef struct
{	
	GPIO_TypeDef *port;    // ���� ����������� ����� (GPIOx)
	uint16_t      pin;     // ��� ����������� ����� (GPIO_PIN_x)
} DI_DescriptStruct;
	 
	 
// ��������� ��������� ��������� DI-������
typedef struct
{
	// ������������ �����	
	uint64_t           *time;        // ��������� �� ������� �������� �������
	uint8_t             diNum;       // ���-�� DI
	uint8_t             periodPoll;  // ������������� ������ DI
	uint8_t             numPoll;     // ���-�� ������ DI
	
	// ����������� ���������
	uint64_t   lastTime;  // ����� ���������� ������
	uint8_t    stepPoll;  // ��� (�����) �������� ������
	uint8_t   *resArr;    // ��������� �� ������ ����������� ������
}DI_ParamStruct;
	 

extern DI_ParamStruct diParam;   // ��������� ��������� DI


#ifdef __cplusplus
}
#endif
#endif
