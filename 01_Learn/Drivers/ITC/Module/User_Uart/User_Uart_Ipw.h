#ifndef __USER_LPUART_IPW__
#define __USER_LPUART_IPW__

#include "User_Uart_Cfg.h"
#include "User_Ip_Usart.h"



extern void User_Uart_Ipw_Init (User_Uart_HWConfigType *HwConfig);

extern Std_ReturnType User_Uart_Ipw_AsyncTransmit (uint8_t u8ChannelId, const uint8_t *u8DataPtr, int16_t i16DataLen);

extern Std_ReturnType User_Uart_Ipw_ReceiveData (uint8_t u8ChannelId, uint8_t *u8Data, uint16_t u16Length, int16_t *i16Remain);

extern Std_ReturnType User_Ip_Ipw_FindByte(uint8_t u8ChannelId, uint8_t u8ByteF,uint16_t *u16Local);

extern Std_ReturnType User_Ip_Ipw_DeleteRxData(uint8_t u8ChannelId, uint16_t u16DlSize);

extern Std_ReturnType User_Ip_Ipw_ReadByte(uint8_t u8ChannelId, uint8_t *u8Data);
#endif /* __USER_LPUART_IPW__ */
