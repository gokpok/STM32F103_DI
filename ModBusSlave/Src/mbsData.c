
// ------------------------------------------------------------------------------------------------
// ?????? ?????? ??????? ?? ????????? ModbusRTU ? ?????? slave-??????????
// ??????????? ?? ??????? ?. ?. (edmahalich@yandex.ua)
// 
// ????????? ????????????? ???????? ?????? ??????
// ------------------------------------------------------------------------------------------------

#include "mbsData.h"


// ?????????? ?????? ??????
volatile MBS_PeripheryStruct mbsPriph;                              // ?????????
volatile MBS_VariablesStruct mbsVar;                                // ????????? ??????????
         uint8_t             mbsRxBuf[MBS_MAX_TRX_DATA * 2 + 10];   // ????? ??????
         uint8_t             mbsTxBuf[MBS_MAX_TRX_DATA * 2 + 10];   // ????? ????????
         uint16_t           *mbsBuf;                                // ????? ?????? ??????
         uint16_t            mbsBufLen;                             // ?????? ?????? ?????? ??????

