
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, ����������� ���������� ������ ������� slave-����������
// ------------------------------------------------------------------------------------------------

#include "mbsHandler.h"
#include "mbsCRC.h"
#include "mbsError.h"
#include "mbsFuncGetRegs.h"
#include "mbsFuncSetRegs.h"
#include "mbsData.h"


// ���������� ���������
uint64_t lastLinkTime;     // ����� ��������� �����


// ������� ������
FuncRes mbs_CheckTimeout(void);   // �������� �������� �����
FuncRes mbs_CheckCRC(void);       // �������� ����������� �����
FuncRes mbs_RequestProc(void);    // ��������� �������



// ���������� ������ ������� ----------------------------------------------------------------------
FuncRes mbs_Handler(void)
{	
	// ���� ��� ������ = 0 (������ �� ����������������� ��������) - ���������� ��������� �������� ��������
	if(*mbsVar.addr == 0) return mbs_CheckTimeout();
	
	// ���� �������� ������ ��� - ���������� ��������� �������� ��������
	if(mbsVar.endReciev == 0) return mbs_CheckTimeout();
	
	// ���������� ���� �������� ������
	mbsVar.endReciev = 0;
	
	// ���� ����� ������� �� ��� - ���������� ��������� �������� ��������
	if(mbsRxBuf[0] != *mbsVar.addr) return mbs_CheckTimeout();
		
	// ���� ����������� ����� �� �������� - ���������� ��������� �������� ��������
	if(mbs_CheckCRC() != FRES_OK) return mbs_CheckTimeout();
		
	// ��������� ��������� ������� � ��������� � ����
	// ��������� �� ������� Ok - ���������� ��������� �������� ��������
	if(mbs_RequestProc() != FRES_OK) return mbs_CheckTimeout();
	
	// ���� ���������� ������� �� ���������, ��...
	lastLinkTime = *mbsPriph.gTick;  // ���������� ����� ��������� �������
	return FRES_OK;                  // ���������� ������������� ���������
} // mbs_Handler



// �������� �������� ����� ------------------------------------------------------------------------
FuncRes mbs_CheckTimeout(void)
{
	// ���� ����� �������� ����� - ���������� ������, ����� - ���������� ����������
	if(*mbsPriph.gTick < (lastLinkTime + ((uint16_t)*mbsVar.timeout)))
		return FRES_NONE;
	else
		return FRES_ERR;
} // mbs_CheckTimeOut()



// �������� ����������� ����� ---------------------------------------------------------------------
FuncRes mbs_CheckCRC(void)
{
	// ������� ����������� ����� �������� ������
	mbsVar.crc = mbs_GetCrc16(mbsRxBuf, (mbsVar.rxLen - 2));
	
	// ���������� ���������� ����� � ����������� � �������
	if((mbsRxBuf[mbsVar.rxLen - 2] == (mbsVar.crc & 0x00ff)) && (mbsRxBuf[mbsVar.rxLen - 1] == (mbsVar.crc >> 8)))
		return FRES_OK;
	else
		return FRES_ERR;
} // mbs_CheckCRC()



// ��������� ������� ------------------------------------------------------------------------------
FuncRes mbs_RequestProc(void)
{
	// ������������ ������ � ������������ � �������� ��������
	switch(mbsRxBuf[1])
	{
		// ������� ��������� ����� ���������
		case MBS_FUNC_GET_REGS:
			return mbs_FuncGetRegs();
		
		// ������� ������� ����� ���������
		case MBS_FUNC_SET_REGS:
			return mbs_FuncSetRegs();
				
		// ���� ������� ������� �� ��������������, ��...
		default:
			mbs_ReturnErr(MBS_ERR_BADFUNC);  // ���������� ����� ������
			return mbs_CheckTimeout();       // ���������� ��������� �������� ��������
	} // switch
} // mbs_RequestProc()
