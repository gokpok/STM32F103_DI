
#ifndef __mbsFuncGetRegs_H
#define __mbsFuncGetRegs_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "ModbusSlave.h"
	 

// ������� ������ �� ������ � �������� ��������� ����� ��������� (0x03)
FuncRes mbs_FuncGetRegs(void);

#ifdef __cplusplus
}
#endif
#endif
