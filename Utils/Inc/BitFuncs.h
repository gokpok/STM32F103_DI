
#ifndef __BitFuncs_H
#define __BitFuncs_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
	 
// ��������� �������� ����
uint8_t GetBit(uint16_t *reg, uint8_t bit);
	 
// ������� �������� ����
void SetBit(uint16_t *reg, uint8_t bit, uint8_t state);
	 
// ������� ���� ��� "������"
void SetBitTrue(uint16_t *reg, uint8_t bit);
	 
// ������� ���� ��� "���"
void SetBitFalse(uint16_t *reg, uint8_t bit);

#ifdef __cplusplus
}
#endif
#endif
