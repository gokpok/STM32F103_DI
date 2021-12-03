
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, �������������� ������ � �������� ������� �������� ����� ��������� (0x10)
// ------------------------------------------------------------------------------------------------

#include "mbsFuncSetRegs.h"
#include "mbsSendData.h"
#include "mbsError.h"
#include "mbsUtils.h"
#include "mbsCRC.h"
#include "mbsData.h"

	 

// ������� ������ �� ������ � �������� ��������� ����� ��������� (0x03) ---------------------------
FuncRes mbs_FuncSetRegs(void)
{
	// �������� ��������� ����� � ������ ������������� ������
	mbsVar.dataBegin = (mbsRxBuf[2] << 8) | mbsRxBuf[3];
	mbsVar.dataNum   = (mbsRxBuf[4] << 8) | mbsRxBuf[5];
	
	// ��������� ����������� ������ �� �����������
	if(mbs_CheckQuerySeries() == FRES_ERR)
		return FRES_ERR;
	
	// ��������� ��������� ������
	mbsTxBuf[0] = *mbsVar.addr;        // ��������� ����� slave-����������
	mbsTxBuf[1] = MBS_FUNC_SET_REGS;  // ��������� ��� ����������� �������
	mbsTxBuf[2] = mbsRxBuf[2];        // ��������� ����� ������� ������������ �������� (Hi)
	mbsTxBuf[3] = mbsRxBuf[3];        // ��������� ����� ������� ������������ �������� (Low)
	mbsTxBuf[4] = mbsRxBuf[4];        // ��������� ���-�� ����������� ��������� (Hi)
	mbsTxBuf[5] = mbsRxBuf[5];        // ��������� ���-�� ����������� ��������� (Low)
	
	// �������� �������� ����� ������������� ������
	mbsVar.dataEnd = mbsVar.dataBegin + mbsVar.dataNum;
	
	mbsVar.count1 = mbsVar.dataBegin;   // 1� ������� ������ ��� ��������� ����� ����������� ������
	mbsVar.count2 = 7;                  // 2� ������� ������ ��� ��������� ����� ����������� ������ � ������
		
	// �������� �� ������ ����������� ������
	for( ; mbsVar.count1 < mbsVar.dataEnd; mbsVar.count1++, mbsVar.count2 += 2)
		mbsBuf[mbsVar.count1] = mbsRxBuf[mbsVar.count2] << 8 | mbsRxBuf[mbsVar.count2 + 1];
	
	// �������� ����������� ����� ��������������� ������ � ��������� � ����� ������
	mbsVar.crc = mbs_GetCrc16(mbsTxBuf, 6);
	mbsTxBuf[6] = mbsVar.crc & 0x00ff;
	mbsTxBuf[7] = mbsVar.crc >> 8;	
	
	// ���������� �������� ������
	mbs_SendDataIni(8);
	
	return FRES_OK;
} // mbs_FuncSetRegs()
