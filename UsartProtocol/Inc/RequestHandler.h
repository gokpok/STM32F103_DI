#include "main.h"
#include "MainInit.h"
#include "mbsCRC.h"


extern uint8_t ResponseBuf[6];
extern uint8_t Rx_Cmplt_Flag;
extern volatile uint32_t uwTick;

void MakeResponse(uint8_t* buf, uint8_t* DI_State);


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void UART_RESET (void);
