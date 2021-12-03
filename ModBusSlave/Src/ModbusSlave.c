
// ------------------------------------------------------------------------------------------------
// ������ ������ ������� �� ��������� ModbusRTU � ������ slave-����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ��������� ���������� ������
// ------------------------------------------------------------------------------------------------

#include "ModbusSlave.h"
#include "mbsInit.h"
#include "mbsInterrupt.h"
#include "mbsHandler.h"



// ������������� slave-��������� ------------------------------------------------------------------
void MBS_Init(MBS_InitStruct *initStruct)
{
	mbs_Init(initStruct);
} // MBS_Init()



// ���������� slave-���������� --------------------------------------------------------------------
FuncRes MBS_Handler(void)
{
	return mbs_Handler();
} // MBS_Handler()



// ���������� ���������� �� USATR (�����/��������) ------------------------------------------------
void MBS_UART_Interrupt()
{
	mbs_UsartInterrupt();
} // MBS_UART_Interrupt()



// ���������� ���������� �� TIM (���������� ������) ------------------------------------------------
void MBS_TIM_Interrupt(void)
{
	mbs_TimInterrupt();
} // MBS_TIM_Interrupt()


