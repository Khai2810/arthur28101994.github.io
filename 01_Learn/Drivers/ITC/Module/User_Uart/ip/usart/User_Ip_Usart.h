#ifndef __USER_IP_USART__
#define __USER_IP_USART__

#include "User_Uart_Cfg.h"
#include "User_Ip_Usart_Types.h"


#define USER_IP_USART_CHANNELID_1      (0U)
#define USER_IP_USART_CHANNELID_2      (1U)
#define USER_IP_USART_CHANNELID_3      (3U)

extern void User_Ip_Usart_Init(User_Uart_HWConfigType *HwConfig);
extern Std_ReturnType User_Ip_Usart_WriteBuffer (uint8_t u8ChannelId, const uint8_t *u8DataPtr, int16_t u16DataLen);
extern Std_ReturnType User_Ip_Usart_ReadBuffer(uint8_t u8ChannelId, uint8_t *u8data, uint16_t u16length, int16_t *i16remain);
extern Std_ReturnType User_Ip_Usart_ReadByte(uint8_t u8ChannelId, uint8_t *u8Data);
extern Std_ReturnType User_Ip_Usart_FindByte(uint8_t u8ChannelId, uint8_t u8ByteF,uint16_t *u16Local);
extern Std_ReturnType User_Ip_Usart_DeleteRxData (uint8_t u8ChannelId, uint16_t u16DlSize);

#endif /* __USER_IP_USART__ */

