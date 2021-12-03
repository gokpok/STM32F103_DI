
// ------------------------------------------------------------------------------------------------
// ������ ��������� �������� ������ ����������
// ����������� �� ������� �. �. (edmahalich@yandex.ua)
// 
// ��������� ��������� ��������� ������� �������
// ------------------------------------------------------------------------------------------------

#include "OutHandler.h"
#include "DigitInput.h"
#include "BitFuncs.h"
#include "stdlib.h"
#include "data.h"


DO_StateStruct *DO_State;   // ��������� �� ������ ��������� �������������� DO
GPIO_PinState   state;      // ��������� ����� GPIO
GPIO_PinState  *lastState;  // ��������� �� ������ ��������� ��������� DO
uint8_t         doNum;      // ���-�� �������������� �������
uint8_t         count;      // ������� ����������� ����


// ������� ���������� ������
void do_SetState(void);

// �������� �������� �� ����� ��� ������
void do_TimeoutCtrl(void);

// �������� ��������� ������
uint8_t do_OnCtrl(void);

// �������� ���������� ������
uint8_t do_OffCtrl(void);


// ������������� ������ ---------------------------------------------------------------------------
void DO_Init(uint8_t num)
{	
	// ������ ��������� ������������ ������
	doNum = num;    // ������ ���-�� �������������� �������
	
	// �������� ������ ��� ������� �������� DO
	DO_State = (DO_StateStruct*) malloc(doNum * sizeof(DO_StateStruct));
	
	// �������� ������ ��� ������� ��������� ��������� DO
	lastState = (GPIO_PinState*) malloc(doNum * sizeof(GPIO_PinState));
} // DO_Init()



// ���������� ������ � ������ -------------------------------------------------------------------
void DO_Add(uint8_t num, GPIO_TypeDef *port, uint16_t pin, uint16_t *stateReg, uint16_t *onCtrlReg,
						uint16_t *offCtrlReg, uint16_t *toCtrlReg, uint16_t *onErrReg, uint16_t *offErrReg, uint8_t bit)
{
	DO_State[num].port       = port;
	DO_State[num].pin        = pin;
	DO_State[num].stateReg   = stateReg;
	DO_State[num].onCtrlReg  = onCtrlReg;
	DO_State[num].offCtrlReg = offCtrlReg;
	DO_State[num].toCtrlReg  = toCtrlReg;
	DO_State[num].onErrReg   = onErrReg;
	DO_State[num].offErrReg  = offErrReg;
	DO_State[num].bit        = bit;
} // DO_Add()



// ���������� ��������� DO ------------------------------------------------------------------------
void DO_Handler(void)
{
	// ��������� ��������� ��������
	for(count = 1; count < doNum; count++)
	{
		do_SetState();      // ������ ��������� ������
		do_TimeoutCtrl();   // ������������ �������� �������� �� �����
		
		// ������������ �������� ���������
		SetBit(DO_State[count].onErrReg, DO_State[count].bit, do_OnCtrl()); 
		
		// ������������ �������� ����������
		SetBit(DO_State[count].offErrReg, DO_State[count].bit, do_OffCtrl());        
		
		// ������ ��������� GPIO-����� ������
		HAL_GPIO_WritePin(DO_State[count].port, DO_State[count].pin, state);
	} // for
} // DO_Handler



// ������� ���������� ������ ----------------------------------------------------------------------
void do_SetState(void)
{
		// ������ ��������� GPIO-����� ������
		state = GetBit(DO_State[count].stateReg, DO_State[count].bit) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET;
	
		// ���� ��������� ����������, ��...
		if(state != lastState[count])
		{
			DO_State[count].changeTime = gTick;   // ���������� ����� ��������� ���������
			lastState[count] = state;             // ��������� ���������
		} // if
} // do_SetState()



// �������� �������� �� ����� ��� ������ ----------------------------------------------------------
void do_TimeoutCtrl(void)
{
	// ���� ��� ������ ����� - ������
	if(link != FRES_ERR) return;
	
	// ���� ��� ������ �� ����� �������� �������� - ������
	if(GetBit(DO_State[count].toCtrlReg, DO_State[count].bit) == 0) return;
	
	// ���� ���������� ������� �� ��������� - ��������� �����
	state = GPIO_PIN_RESET;
} // do_TimeoutCtrl()



// �������� ��������� ������ ----------------------------------------------------------------------
uint8_t do_OnCtrl(void)
{
	// ���� ����� �������� - ������
	if(state == GPIO_PIN_RESET) return 0;
	
	// ���� ��� ������ �� ����� �������� ��������� - ������
	if(GetBit(DO_State[count].onCtrlReg, DO_State[count].bit) == 0) return 0;
	
	// ���� ����� �������� �� ������� - ������
	if(gTick < (DO_State[count].changeTime + TIME_CTRL_ON)) return 0;
	
	// ���� ��� ������� �� ������ - ������ ���� ������� ������ ���������
	if(DI_State[count] == 0)
		return 1;
	else
		return 0;
} // do_OnCtrl()



// �������� ���������� ������ ----------------------------------------------------------------------
uint8_t do_OffCtrl(void)
{
	// ���� ����� ������� - ������
	if(state == GPIO_PIN_SET) return 0;
	
	// ���� ��� ������ �� ����� �������� ���������� - ������
	if(GetBit(DO_State[count].offCtrlReg, DO_State[count].bit) == 0) return 0;
	
	// ���� ����� �������� �� ������� - ������
	if(gTick < (DO_State[count].changeTime + TIME_CTRL_OFF)) return 0;
	
	// ���� ��� ������� �� ������ - ���������� ���� ������� ������ ���������
	if(DI_State[count] == 0)
		return 0;
	else
		return 1;
} // do_OffCtrl()
