
#ifndef __mbsCRC_H
#define __mbsCRC_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"

	 
// ��������� ����������� ����� ������
uint16_t mbs_GetCrc16(uint8_t *buf, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif
