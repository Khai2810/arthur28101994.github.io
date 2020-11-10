
#include "User_Uart.h"
#include "User_Uart_Ipw.h"

static User_Uart_ConfigType *UartConfigPtr = NULL;
static uint8_t User_Uart_RxBuffer[USER_UART_NUMBEROFCHANNEL_USED][USER_UART_MAX_MESSAGE_LENGTH];

void User_Uart_Init(const User_Uart_ConfigType *UartConfig)
{

	uint8_t u8ChannelCount = 0U;
	User_Uart_HWConfigType HWConfig;


	UartConfigPtr = (User_Uart_ConfigType *)UartConfig;

    for(u8ChannelCount = 0u; u8ChannelCount < UartConfigPtr->numberChannel; u8ChannelCount++)
    {
    	HWConfig.ParityMode = UartConfigPtr->ChannelConfig[u8ChannelCount].ParityMode;
    	HWConfig.StopBitCount = UartConfigPtr->ChannelConfig[u8ChannelCount].StopBitCount;
    	HWConfig.u32SourceClock = UartConfigPtr->ChannelConfig[u8ChannelCount].u32SourceClock;
    	HWConfig.u32Baudrate = UartConfigPtr->ChannelConfig[u8ChannelCount].u32Baudrate;
    	HWConfig.SlipStatus = UartConfigPtr->ChannelConfig[u8ChannelCount].SlipStatus;
    	HWConfig.u8HwChannelID = UartConfigPtr->ChannelConfig[u8ChannelCount].u8HwChannelID;

        User_Uart_Ipw_Init(&HWConfig);
    }
}


Std_ReturnType User_Uart_AsyncTransmit(uint8_t u8ChannelId, uint8_t *u8DataPtr, uint16_t u16DataLen)
{
    uint8_t u8count;
    uint8_t ChannelID = 0xFFu;
    Std_ReturnType ret = E_NOT_OK;

    if(UartConfigPtr == NULL)
    {
    	return E_NOT_OK;
    }

    for(u8count = 0;u8count < UartConfigPtr->numberChannel;u8count++)
    {
        if(UartConfigPtr->ChannelConfig[u8count].u8HwChannelID == u8ChannelId)
        {
            ChannelID = u8count;
            break;
        }
    }

    if(ChannelID == 0xFF)
    {
        return E_NOT_OK;
    }

    if(UartConfigPtr->ChannelConfig[ChannelID].SlipStatus == USER_UART_SLIP_ENABLE)
    {
    	if(u16DataLen > USER_UART_MAX_MESSAGE_LENGTH)
    	{
    		return E_NOT_OK;
    	}
         ret = User_Slip_SendFrame(u8ChannelId,u8DataPtr,u16DataLen);
    }
    else
    {
        ret = User_Uart_Ipw_AsyncTransmit(u8ChannelId,u8DataPtr,u16DataLen);
    }

    return ret;
}


Std_ReturnType User_Uart_Received (uint8_t u8ChannelId, uint8_t **u8AddData, uint16_t u16DataLen, int16_t *i16RemainPtr)
{
    uint8_t u8count = 0x00u;
    uint8_t ChannelID = 0xFFu;
    uint16_t DataLength = 0x00u;
    Std_ReturnType ret = E_NOT_OK;

    if(UartConfigPtr == NULL)
    {
        return E_NOT_OK;
    }

    for(u8count = 0;u8count < UartConfigPtr->numberChannel;u8count++)
    {
        if(UartConfigPtr->ChannelConfig[u8count].u8HwChannelID == u8ChannelId)
        {
            ChannelID = u8count;
            break;
        }
    }

    if(ChannelID == 0xFF)
    {
        return E_NOT_OK;
    }

    if(UartConfigPtr->ChannelConfig[ChannelID].SlipStatus == USER_UART_SLIP_ENABLE)
    {
        if (E_NOT_OK == User_Slip_ReceivedFrame(u8ChannelId,&User_Uart_RxBuffer[ChannelID][0],&DataLength))
        {
        	return E_NOT_OK;
        }

        *i16RemainPtr = DataLength - u16DataLen;
        ret = E_OK;
    }
    else
    {
        ret = User_Uart_Ipw_ReceiveData(u8ChannelId,&User_Uart_RxBuffer[ChannelID][0],u16DataLen,i16RemainPtr);
    }

    *u8AddData = &User_Uart_RxBuffer[ChannelID][0];
    return ret;
}





