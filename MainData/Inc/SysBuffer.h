
#ifndef __SysBuffer_H
#define __SysBuffer_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "data.h"

// ��������������� ������ � ������� ������

// ����������� ��� ���������� ����������
#define DEVICE_CODE       mData[0]     // ��� ����������
#define PROG_INFO         mData[1]     // ������ �� (Hi) + ��������� �� (Low)
	 
// ����������� ������� ������ ��������� DO
#define DO_STATE_1   mData[2]
#define DO_STATE_2   mData[3]
	 
// ����������� ������� ����������
#define CONTROL_REG   mData[4]
	 	 
// ����������� ������� ������ DO � ������� ���������/����������
#define ON_OFF_ERR_DO  mData[5]

// ����������� ������� ������ ������ ���������
#define ON_ERR_1     mData[6]
#define ON_ERR_2     mData[7]

// ����������� ������� ������ ������ ����������
#define OFF_ERR_1     mData[8]
#define OFF_ERR_2     mData[9]

// ����������� ������� ������ �������� ��������
#define TIMEOUT_CTRL_1     mData[10]
#define TIMEOUT_CTRL_2     mData[11]

// ����������� ������� ������ �������� ���������
#define ON_CTRL_1     mData[12]
#define ON_CTRL_2     mData[13]

// ����������� ������� ������ �������� ����������
#define OFF_CTRL_1     mData[14]
#define OFF_CTRL_2     mData[15]
	 

#define LINK_TIMEOUT      mData[16]    // �������� ������� �������� �����
#define TIME_CTRL_ON      mData[17]    // �������� ������� �������� ��������� DO
#define TIME_CTRL_OFF     mData[18]    // �������� ������� �������� ���������� DO

// ����������� ��������� ������ ������ ���������
#define ON_ERR_DO1    (ON_ERR_1 & 0x8000)
#define ON_ERR_DO2    (ON_ERR_1 & 0x4000)
#define ON_ERR_DO3    (ON_ERR_1 & 0x2000)
#define ON_ERR_DO4    (ON_ERR_1 & 0x1000)
#define ON_ERR_DO5    (ON_ERR_1 & 0x0800)
#define ON_ERR_DO6    (ON_ERR_1 & 0x0400)
#define ON_ERR_DO7    (ON_ERR_1 & 0x0200)
#define ON_ERR_DO8    (ON_ERR_1 & 0x0100)
#define ON_ERR_DO9    (ON_ERR_1 & 0x0080)
#define ON_ERR_DO10   (ON_ERR_1 & 0x0040)
#define ON_ERR_DO11   (ON_ERR_1 & 0x0020)
#define ON_ERR_DO12   (ON_ERR_1 & 0x0010)
#define ON_ERR_DO13   (ON_ERR_1 & 0x0008)
#define ON_ERR_DO14   (ON_ERR_1 & 0x0004)
#define ON_ERR_DO15   (ON_ERR_1 & 0x0002)
#define ON_ERR_DO16   (ON_ERR_1 & 0x0001)
#define ON_ERR_DO17   (ON_ERR_2 & 0x8000)
#define ON_ERR_DO18   (ON_ERR_2 & 0x4000)

// ����������� ��������� ������ ������ ����������
#define OFF_ERR_DO1    (OFF_ERR_1 & 0x8000)
#define OFF_ERR_DO2    (OFF_ERR_1 & 0x4000)
#define OFF_ERR_DO3    (OFF_ERR_1 & 0x2000)
#define OFF_ERR_DO4    (OFF_ERR_1 & 0x1000)
#define OFF_ERR_DO5    (OFF_ERR_1 & 0x0800)
#define OFF_ERR_DO6    (OFF_ERR_1 & 0x0400)
#define OFF_ERR_DO7    (OFF_ERR_1 & 0x0200)
#define OFF_ERR_DO8    (OFF_ERR_1 & 0x0100)
#define OFF_ERR_DO9    (OFF_ERR_1 & 0x0080)
#define OFF_ERR_DO10   (OFF_ERR_1 & 0x0040)
#define OFF_ERR_DO11   (OFF_ERR_1 & 0x0020)
#define OFF_ERR_DO12   (OFF_ERR_1 & 0x0010)
#define OFF_ERR_DO13   (OFF_ERR_1 & 0x0008)
#define OFF_ERR_DO14   (OFF_ERR_1 & 0x0004)
#define OFF_ERR_DO15   (OFF_ERR_1 & 0x0002)
#define OFF_ERR_DO16   (OFF_ERR_1 & 0x0001)
#define OFF_ERR_DO17   (OFF_ERR_2 & 0x8000)
#define OFF_ERR_DO18   (OFF_ERR_2 & 0x4000)

extern uint16_t *mData;     // ������ �� �������� ������ ������
extern uint16_t mDataLen;   // ������ ��������� ������� ������

void SysBufInit(uint16_t len);   // ������������� ��������� ������� ������

#ifdef __cplusplus
}
#endif
#endif
