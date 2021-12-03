
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, �������������� ������ � �������� ��������� �������� ����� ��������� (0x03)
// ------------------------------------------------------------------------------------------------

#include "mbsFuncGetRegs.h"
#include "mbsSendData.h"
#include "mbsError.h"
#include "mbsUtils.h"
#include "mbsCRC.h"
#include "mbsData.h"

	 

// ������� ������ �� ������ � �������� ��������� ����� ��������� (0x03) ---------------------------
FuncRes mbs_FuncGetRegs(void)
{
	// �������� ��������� ����� � ������ ������������� ������
	mbsVar.dataBegin = (mbsRxBuf[2] << 8) | mbsRxBuf[3];
	mbsVar.dataNum   = (mbsRxBuf[4] << 8) | mbsRxBuf[5];
	
	// ��������� ����������� ������ �� �����������
	if(mbs_CheckQuerySeries() == FRES_ERR)
		return FRES_ERR;
	
	// ��������� ��������� ������
	mbsTxBuf[0] = *mbsVar.addr;        // ��������� ����� slave-����������
	mbsTxBuf[1] = MBS_FUNC_GET_REGS;  // ��������� ��� ����������� �������
	mbsTxBuf[2] = mbsVar.dataNum * 2; // ��������� ���-�� ������ � ������
	
	// �������� �������� ����� ������������� ������
	mbsVar.dataEnd = mbsVar.dataBegin + mbsVar.dataNum;
	
	mbsVar.count1 = mbsVar.dataBegin;   // ������ ������� ������ ��� ��������� ����� ����������� ������
	mbsVar.count2 = 3;                  // ������ ������� ������ ��� ��������� ����� ����������� ������ � ������
		
	// ��������� � ����� ����������� ������
	for( ; mbsVar.count1 <= mbsVar.dataEnd; mbsVar.count1++, mbsVar.count2++)
	{
		mbsTxBuf[mbsVar.count2]   = mbsBuf[mbsVar.count1] >> 8;
		mbsTxBuf[++mbsVar.count2] = mbsBuf[mbsVar.count1] & 0x00FF;
	} // for	
	
	// �������� ����������� ����� ��������������� ������ � ��������� � ����� ������
	mbsVar.crc = mbs_GetCrc16(mbsTxBuf, mbsVar.count2 - 2);
	mbsTxBuf[mbsVar.count2 - 2] = mbsVar.crc & 0x00ff;
	mbsTxBuf[mbsVar.count2 - 1] = mbsVar.crc >> 8;	
	
	// ���������� �������� ������
	mbs_SendDataIni(mbsVar.count2);
	
	return FRES_OK;
} // mbs_FuncGetRegs()
