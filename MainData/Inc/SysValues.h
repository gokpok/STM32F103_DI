
#ifndef __SysValues_H
#define __SysValues_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "data.h"
#include "main.h"
// C������ ��������� ����� (���������� ����� �� ������, ����)	 
extern uint64_t gTick;
	 
// ��������� ����� � master-�����������
extern FuncRes link;
	 
// ����� slave-����������
extern uint8_t sAddr;

#ifdef __cplusplus
}
#endif
#endif
