
#ifndef __data_H
#define __data_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
	 
// ���������� �������� ������
#include "SysBuffer.h"
#include "SysValues.h"


void MainDataInit(uint16_t mDataLen);   // ������������� ������ �������� ������ �������
	 
	 
#ifdef __cplusplus
}
#endif
#endif
