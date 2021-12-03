
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ��������� ������������� ������
// ------------------------------------------------------------------------------------------------

#include "mbsInit.h"
#include "mbsData.h"



// ������������� ���������� modbus master ---------------------------------------------------------
void mbs_Init(MBS_InitStruct *initStruct)
{
	mbsBuf    = initStruct->buf;
	mbsBufLen = initStruct->bufLen;
	
	mbsVar.addr    = initStruct->addr;
	mbsVar.timeout = initStruct->timeout;
	
	mbsPriph.uart    = initStruct->uart;
	mbsPriph.tim     = initStruct->tim;
	mbsPriph.dirPort = initStruct->dirPort;
	mbsPriph.dirPin  = initStruct->dirPin;	
	mbsPriph.gTick   = initStruct->gTick;
} // mbs_Init()
