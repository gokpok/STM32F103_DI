

#include "MainInit.h"
#include "clock.h"
//#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "data.h"

#include "DigitInput.h"
#include "OutHandler.h"

#define MDATA_LEN 23        //Number of processed pins


uint8_t RxStart[3]={0};          //Command of start making data package


// ������� ������������� � ��������� ��������� � ���������� ������� ������� -----------------------
void InitSystem(void)
{
	
	// �������������� ������ �������� ������ �������
	MainDataInit(MDATA_LEN);
	
	
	// �������������� ������ ���������� ������
	// (���-�� DI ������ �� 1 ������, �.�. DI-0 �� ����������)
	DI_Init(24, 10, 1, &gTick);
	DI_AddInput(1, GPIOB, GPIO_PIN_9);    // ���������� DI �������� ����� ������ 1
	DI_AddInput(2, GPIOB, GPIO_PIN_8);    // ���������� DI �������� ����� ������ 2
	DI_AddInput(3, GPIOB, GPIO_PIN_7);    // ���������� DI �������� ����� ������ 3
	DI_AddInput(4, GPIOB, GPIO_PIN_6);    // ���������� DI �������� ����� ������ 4
	DI_AddInput(5, GPIOB, GPIO_PIN_0);    // ���������� DI �������� ����� ������ 5
	DI_AddInput(6, GPIOA, GPIO_PIN_11);    // ���������� DI �������� ����� ������ 6
	DI_AddInput(7, GPIOA, GPIO_PIN_8);    // ���������� DI �������� ����� ������ 7
	DI_AddInput(8, GPIOA, GPIO_PIN_7);    // ���������� DI �������� ����� ������ 8
	DI_AddInput(9, GPIOA, GPIO_PIN_6);   // ���������� DI �������� ����� ������ 9
	DI_AddInput(10, GPIOA, GPIO_PIN_5);  // ���������� DI �������� ����� ������ 10
	DI_AddInput(11, GPIOA, GPIO_PIN_4);  // ���������� DI �������� ����� ������ 11
	DI_AddInput(12, GPIOA, GPIO_PIN_3);   // ���������� DI �������� ����� ������ 12
	DI_AddInput(13, GPIOA, GPIO_PIN_2);   // ���������� DI �������� ����� ������ 13
	DI_AddInput(14, GPIOA, GPIO_PIN_1);   // ���������� DI �������� ����� ������ 14
	DI_AddInput(15, GPIOA, GPIO_PIN_0);  // ���������� DI �������� ����� ������ 15
	DI_AddInput(16, GPIOB, GPIO_PIN_15);  // ���������� DI �������� ����� ������ 16
	DI_AddInput(17, GPIOB, GPIO_PIN_14);  // ���������� DI �������� ����� ������ 17
	DI_AddInput(18, GPIOB, GPIO_PIN_13);   // ���������� DI �������� ����� ������ 18
	DI_AddInput(19, GPIOB, GPIO_PIN_12);   // ���������� DI �������� ����� ������ 19
	DI_AddInput(20, GPIOB, GPIO_PIN_11);   // ���������� DI �������� ����� ������ 20
	DI_AddInput(21, GPIOB, GPIO_PIN_10);   // ���������� DI �������� ����� ������ 21
	DI_AddInput(22, GPIOC, GPIO_PIN_14);   // ���������� DI �������� ����� ������ 22
	DI_AddInput(23, GPIOC, GPIO_PIN_15);   // ���������� DI �������� ����� ������ 23
	//DI_AddInput(24, GPIOA, GPIO_PIN_4);   // ���������� DI ���� 5 ������� ����������
	
	// Start UART recieve in Interrupt mode
	HAL_UART_Receive_IT(&huart1,RxStart,3);  //Receive package
	
//  MX_IWDG_Init();           // �������������� ���������� ������
} // InitSystem()
