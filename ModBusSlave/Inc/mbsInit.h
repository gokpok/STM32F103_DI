
#ifndef __mbsInit_H
#define __mbsInit_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "ModbusSlave.h"
	 
// ������������� ������
void mbs_Init(MBS_InitStruct *initStruct);   // ��� ������ ���������� RS485

#ifdef __cplusplus
}
#endif
#endif
