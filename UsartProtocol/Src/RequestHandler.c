
#include "RequestHandler.h"

uint8_t ResponseBuf[6];  //Buffer to form response
uint8_t Rx_Cmplt_Flag=0;


void MakeResponse(uint8_t* buf, uint8_t* DI_State)
{
	
	//Valuable part of response ( FU1-18 and KM2-5 )  - 4 byte
	//Each bite depicts state of Digital Input. For example 0b000101 means, that DI #1 and #3 is HIGH, rest is LOW
	//---------------------------------------------------------------------------------------------------
	buf[0] = DI_State[1]<<0 | DI_State
	[2]<<1 | DI_State[3]<<2 | DI_State[4]<<3 |
	DI_State[5]<<4 | DI_State[6]<<5 | DI_State[7]<<6 | DI_State[8]<<7;
	
	buf[1] = DI_State[9]<<0 | DI_State[10]<<1 | DI_State[11]<<2 | DI_State[12]<<3 |
	DI_State[13]<<4 | DI_State[14]<<5 | DI_State[15]<<6 | DI_State[16]<<7;
	
	buf[2] = DI_State[17]<<0 | DI_State[18]<<1;
	
	buf[3] = DI_State[19]<<4 | DI_State[20]<<5 | DI_State[21]<<6 | DI_State[22]<<7; 
	
	buf[3] |= 0x0F;  //Additional part of last valuable byte, that makes CRC stronger (not zero) 
	
	//---------------------------------------------------------------------------------------------------
	
	//Making CRC part
	buf[4] = mbs_GetCrc16(buf,4) & 0x0f;
	buf[5] = mbs_GetCrc16(buf,4) >> 8;
	
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//This function is called when the reception is complete
	
	//If start byte is 0xFF and CRC16 matches set Flag of complete receiving
	if ((RxStart[2] ==  mbs_GetCrc16(RxStart,1)>>8) 
	 && (RxStart[1] == (mbs_GetCrc16(RxStart,1) & 0x0f)) 
	 && (RxStart[0] == 0xFF) )
	 
	Rx_Cmplt_Flag = 1;
	
	//Start Receiving again
	HAL_UART_Receive_IT(&huart1,RxStart,3);
	
}

void UART_RESET (void)
{
	static uint32_t uwTick_prev;
	
	if (Rx_Cmplt_Flag == 0)																					//if there is flag of cmpl receive is reset
	{
		if (uwTick>=(uwTick_prev+500))																//and that lasts for more then 0.5 sec
			HAL_UART_Receive_IT(&huart1,RxStart,3);											//Start Receiving again
	}
	else
	uwTick_prev=uwTick;																							//remember last time, when flag cmpl receive was set
	
}

