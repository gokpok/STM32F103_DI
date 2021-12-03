
#ifndef __mbsError_H
#define __mbsError_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
	 
	 
// ������������ ������ � ��������
typedef enum
{
	MBS_ERR_BADFUNC   = 0x01,   // ������������ ������� �������
	MBS_ERR_BADADDR   = 0x02,   // ����� ������, ��������� � �������, ����������
} MBS_ErrEnum;
	 

// ������� ������ �� ������ � �������
void mbs_ReturnErr(MBS_ErrEnum err);

#ifdef __cplusplus
}
#endif
#endif
