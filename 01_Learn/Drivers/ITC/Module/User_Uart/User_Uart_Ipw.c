
#include "User_Uart_Ipw.h"

void User_Uart_Ipw_Init (User_Uart_HWConfigType *HwConfig)
{

    if ((HwConfig->u8HwChannelID >= USER_UART_CHANNEL_USART1) && (HwConfig->u8HwChannelID <= USER_UART_CHANNEL_USART6))
    {
        HwConfig->u8HwChannelID = HwConfig->u8HwChannelID - USER_UART_CHANNEL_USART1;
        User_Ip_Usart_Init(HwConfig);
    }
}

Std_ReturnType User_Uart_Ipw_AsyncTransmit (uint8_t u8ChannelId, const uint8_t *u8DataPtr, int16_t i16DataLen)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8_t channelID = u8ChannelId;

    if ((channelID >= USER_UART_CHANNEL_USART1) && (channelID <= USER_UART_CHANNEL_USART6))
    {
        channelID = channelID - USER_UART_CHANNEL_USART1;
        ret = User_Ip_Usart_WriteBuffer(channelID,u8DataPtr,i16DataLen);
    }

    return ret;
}

Std_ReturnType User_Uart_Ipw_ReceiveData (uint8_t u8ChannelId, uint8_t *u8Data, uint16_t u16Length, int16_t *i16Remain)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8_t channelID = u8ChannelId;


    if ((channelID >= USER_UART_CHANNEL_USART1) && (channelID <= USER_UART_CHANNEL_USART6))
    {
        channelID = channelID - USER_UART_CHANNEL_USART1;
        ret = User_Ip_Usart_ReadBuffer(channelID,u8Data,u16Length,i16Remain);
    }

    return ret;
}

Std_ReturnType User_Ip_Ipw_FindByte (uint8_t u8ChannelId, uint8_t u8ByteF, uint16_t *u16Local)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8_t channelID = u8ChannelId;

    if ((channelID >= USER_UART_CHANNEL_USART1) && (channelID < USER_UART_CHANNEL_USART6))
    {
        channelID = channelID - USER_UART_CHANNEL_USART1;
        ret = User_Ip_Usart_FindByte(channelID,u8ByteF,u16Local);
    }

    return ret;
}

Std_ReturnType User_Ip_Ipw_DeleteRxData(uint8_t u8ChannelId, uint16_t u16DlSize)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8_t channelID;
    channelID = u8ChannelId;

    if ((channelID >= USER_UART_CHANNEL_USART1) && (channelID < USER_UART_CHANNEL_USART6))
    {
        channelID = channelID - USER_UART_CHANNEL_USART1;
        ret = User_Ip_Usart_DeleteRxData(channelID,u16DlSize);
    }

    return ret;
}

Std_ReturnType User_Ip_Ipw_ReadByte(uint8_t u8ChannelId, uint8_t *u8Data)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8_t channelID = u8ChannelId;

    if ((channelID >= USER_UART_CHANNEL_USART1) && (channelID < USER_UART_CHANNEL_USART6))
    {
        channelID = channelID - USER_UART_CHANNEL_USART1;
        ret = User_Ip_Usart_ReadByte(channelID,u8Data);
    }
    return ret;
}





