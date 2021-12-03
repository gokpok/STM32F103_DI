
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ���������, ��������������� ��������������� ������� ������
// ------------------------------------------------------------------------------------------------

#include "mbsUtils.h"
#include "mbsError.h"
#include "mbsData.h"


// �������� ����������� ����� ������������� ������
FuncRes mbs_CheckQuerySeries(void)
{
	// ��������� �� ����������� ������ ����������� �����	
	if(mbsVar.dataNum > MBS_MAX_TRX_DATA)
	{
		mbs_ReturnErr(MBS_ERR_BADADDR);
		return FRES_ERR;
	} // if
	
	// ��������� �� ����� �� ������� ������� ������
	if((mbsVar.dataBegin + mbsVar.dataNum) >= mbsBufLen)
	{
		mbs_ReturnErr(MBS_ERR_BADADDR);
		return FRES_ERR;
	} // if
	
	// ���� ���������� ������� �� ��������� - ���������� ������������� ����������
	return FRES_OK;
} // mbs_CheckQuerySeries()
