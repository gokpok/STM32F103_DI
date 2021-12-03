
// ------------------------------------------------------------------------------------------------
// ������ ������ ���������� ������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ��������� ���������� ������
// C�������� DI ��������  � ������� DI_State, ��� 
//   - ������ - ����� DI, �������� ��� ���������� ����� � ������;
//   - �������� �������� ��� ��������� DI: 0 - low; 1 - hi.
// ------------------------------------------------------------------------------------------------

#include "DigitInput.h"
#include "diDefines.h"
#include "stdlib.h"


uint8_t            *DI_State;  // ��������� �� ������ ��������� �������������� DI
DI_ParamStruct      diParam;   // ��������� ��������� DI
DI_DescriptStruct  *di;        // ��������� �� ������ �������� DI
uint8_t							test[100];

void    DI_PoolStep(uint8_t *resArr);    // ���������� ���� ������
void    DI_AcceptResult(void);           // ���������� ���������� �������
uint8_t DI_CheckPollRes(uint8_t numDI);  // �������� ���������� ������


// ������������� DI ������ ------------------------------------------------------------------------
void DI_Init(uint8_t diNum, uint8_t periodPoll, uint8_t numPoll, uint64_t *time)
{
	// ��������� �������:
	// diNum       - ���-�� DI
	// periodPoll  - ������������� ������ DI (����)
	// numPoll     - ���-�� ������ DI
	// time        - ��������� �� ������� ������� �������
	
	// ������ ��������� ������������ ������
	diParam.diNum      = diNum;
	diParam.periodPoll = periodPoll;
	diParam.numPoll    = numPoll;
	diParam.time       = time;
	
	// ������������� �������� �������� ����������� ����������
	// ����� ���������� ������ ������ ������ �������� �� �������� �������� ������ ������
	diParam.lastTime = *time + 500;
	diParam.stepPoll = 0;
	
	// �������� ������ ��� ������� �������� DI
	di = (DI_DescriptStruct*) malloc(diNum * sizeof(DI_DescriptStruct));
	
	// �������� ������ ��� ������� ����������� �������
	diParam.resArr = (uint8_t*) malloc(diNum * numPoll * sizeof(uint8_t));
	
	// �������� ������ ��� ������� ��������� �������������� DI
	DI_State = (uint8_t*) malloc(diNum * sizeof(uint8_t));
} // DI_Init()



// ���������� ����� � DI ������ -------------------------------------------------------------------
void DI_AddInput(uint8_t diNum, GPIO_TypeDef *port, uint16_t pin)
{
	di[diNum].port = port;
	di[diNum].pin  = pin;
} // DI_AddInput()



// ���������� ��������� DI ------------------------------------------------------------------------
FuncRes DI_Handler(void)
{
	// ���� ����� ���������� ������ �� ������� - ������
	if(*diParam.time < (diParam.lastTime + diParam.periodPoll))
		return FRES_NONE;
	
	// ������ ��� ������ DI � �������� � ���������� ������� �������
	// ����������, ��������������� �������� ���� ������
	DI_PoolStep(&diParam.resArr[diParam.stepPoll * diParam.diNum]);
	
	// ����������� ��� ������
	diParam.stepPoll++;
	
	// ���������� ����� ������
	diParam.lastTime = *diParam.time;
			
	// ���� �� ��� ���� ������ ��������� - ������
	if(diParam.stepPoll < diParam.numPoll)
		return FRES_NONE;
	
	// ���������� ��� ������
	diParam.stepPoll = 0;
	
	// ��������� ��������� �������
	DI_AcceptResult();
	return FRES_OK;
} // DI_Handler



// ���������� ���� ������ -------------------------------------------------------------------------
void DI_PoolStep(uint8_t *resArr)
{
	// ���������� � ���������� DI
	for(uint8_t i = 0; i < diParam.diNum; i++)
		resArr[i] = HAL_GPIO_ReadPin(di[i].port, di[i].pin);
} // DI_PoolStep()



// ���������� ���������� ������� ------------------------------------------------------------------
void DI_AcceptResult(void)
{
	// ���������� � ��������� ���������� ������� ��� ������ DI
	for(uint8_t i = 0; i < diParam.diNum; i++)
	{	DI_State[i] = DI_CheckPollRes(i); test[i]=DI_State[i];}
	
} // DI_AcceptResult()



// �������� ���������� ������ ---------------------------------------------------------------------
uint8_t DI_CheckPollRes(uint8_t numDI)
{
	// ���������� ���������� ������ ��� ��������� DI
	for(uint8_t i = 0; i < diParam.numPoll; i++)
	{
		// ���� � ������� ���� ������������� ��������� - ���������� 0
		if(diParam.resArr[numDI + (i * diParam.diNum)] != GPIO_PIN_SET)
			return 0;
	} // for
		
	return 1;
} // DI_CheckPollRes()
