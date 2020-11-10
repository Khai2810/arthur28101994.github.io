#ifndef __USER_UART__
#define __USER_UART__


#include "User_Uart_Cfg.h"
#include "User_Uart_Types.h"

extern void User_Uart_Init(const User_Uart_ConfigType *UartConfig);
extern Std_ReturnType User_Uart_AsyncTransmit(uint8_t u8ChannelId, uint8_t *DataPtr, uint16_t DataLen);
extern Std_ReturnType User_Uart_Received (uint8_t u8ChannelId, uint8_t **u8AddData, uint16_t u16DataLen, int16_t *i16RemainPtr);


#endif /* __USER_UART__ */
