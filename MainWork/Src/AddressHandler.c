
// ------------------------------------------------------------------------------------------------
// ������ ��������� �������� ������ ����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ��������� ��������� ������ slave-����������
// ------------------------------------------------------------------------------------------------

#include "AddressHandler.h"
#include "DigitInput.h"
#include "data.h"

// ������ ���������� ������
#define PERIOD_ADDR_UPDATE   500
	 	 
// ����������� ��������� ����� ������
#define ADDR_BIT_0   DI_State[19]
#define ADDR_BIT_1   DI_State[20]
#define ADDR_BIT_2   DI_State[21]
#define ADDR_BIT_3   DI_State[22]
#define ADDR_BIT_4   DI_State[23]
#define ADDR_BIT_5   DI_State[24]

// ����� ���������� ����������
uint64_t lastAddrUpdate = 0;

// ��������� �������� �������
uint8_t tempAddr;


// ���������� ������ ���������� -------------------------------------------------------------------
void AddrHandler(uint8_t *addr)
{
	// ���� ����� ��������� ������ �� ������� - ������
	if(gTick < (lastAddrUpdate + PERIOD_ADDR_UPDATE)) return;
	
	// ���������� ��������� ����������
	tempAddr = 0;
	
	if(ADDR_BIT_5 != 0) tempAddr &= 0xffdf; else tempAddr |= 0x0020;
	if(ADDR_BIT_4 != 0) tempAddr &= 0xffef; else tempAddr |= 0x0010;
	if(ADDR_BIT_3 != 0) tempAddr &= 0xfff7; else tempAddr |= 0x0008;
	if(ADDR_BIT_2 != 0) tempAddr &= 0xfffb; else tempAddr |= 0x0004;
	if(ADDR_BIT_1 != 0) tempAddr &= 0xfffd; else tempAddr |= 0x0002;
	if(ADDR_BIT_0 != 0) tempAddr &= 0xfffe; else tempAddr |= 0x0001;
	
	// ����������� �������� ��������� ������ � ���������� �����
	sAddr = tempAddr;
	
	lastAddrUpdate = gTick;
} // AddrHandler()
