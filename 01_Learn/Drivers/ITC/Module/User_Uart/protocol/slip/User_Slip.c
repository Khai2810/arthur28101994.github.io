#include "User_Slip.h"

const User_Uart_ConfigType * UartConfigPtr = &User_Uart_ConfigPtr;
static User_Slip_Buffer User_Slip_TxBuffer[USER_UART_NUMBEROFCHANNEL_USED];
static User_Slip_Buffer User_Slip_RxBuffer[USER_UART_NUMBEROFCHANNEL_USED];

void User_Slip_Init(void)
{
    uint16_t u16count = 0;
    uint8_t u8ChannelCount;

    for (u8ChannelCount = 0U; u8ChannelCount < USER_UART_NUMBEROFCHANNEL_USED; u8ChannelCount++)
    {
        User_Slip_RxBuffer[u8ChannelCount].u16DataLen = 0U;
        for(u16count = 0; u16count < USER_SLIP_BUFFERSIZE; u16count++)
        {
            User_Slip_RxBuffer[u8ChannelCount].u8DataPtr[u16count] = 0U;
        }
    }
}

Std_ReturnType User_Slip_SendFrame(uint8_t u8ChannelId, uint8_t *u8DataPtr, uint16_t u16Length)
{
    uint8_t u8Count;
    uint8_t u8NumberSlipBuffer = 0xFFu;
	uint8_t u8Val;
    uint16_t u16CountIdx;
    uint16_t u16LenCount = 0;
    Std_ReturnType ret = E_NOT_OK;

    for(u8Count = 0; u8Count < UartConfigPtr->numberChannel; u8Count++)
    {
        if(UartConfigPtr->ChannelConfig[u8Count].u8HwChannelID == u8ChannelId)
        {
        	u8NumberSlipBuffer = u8Count;
            break;
        }
    }

    if(u8NumberSlipBuffer == 0xFF)
    {
        return ret;
    }

    User_Slip_Buffer *TxBufPtr = &User_Slip_TxBuffer[u8NumberSlipBuffer];

    if (u16Length < USER_SLIP_BUFFERSIZE)
    {
        u16LenCount = 0;
        TxBufPtr->u8DataPtr[u16LenCount] = USER_SLIP_END;
        u16LenCount++;

        for (u16CountIdx = 0; u16CountIdx < u16Length; u16CountIdx++)
        {
            u8Val = u8DataPtr[u16CountIdx];
            switch (u8Val)
            {
                case USER_SLIP_END:
                    TxBufPtr->u8DataPtr[u16LenCount] = USER_SLIP_ESC;
                    u16LenCount++;
                    TxBufPtr->u8DataPtr[u16LenCount] = USER_SLIP_ESC_END;
                    u16LenCount++;
                    break;
                case USER_SLIP_ESC:
                    TxBufPtr->u8DataPtr[u16LenCount] = USER_SLIP_ESC;
                    u16LenCount++;
                    TxBufPtr->u8DataPtr[u16LenCount] = USER_SLIP_ESC_ESC;
                    u16LenCount++;
                    break;
                default:
                    TxBufPtr->u8DataPtr[u16LenCount] = u8Val;
                    u16LenCount++;
                    break;
            }
        }
        TxBufPtr->u8DataPtr[u16LenCount] = USER_SLIP_END;
        u16LenCount++;
        TxBufPtr->u16DataLen =  u16LenCount;

        ret = User_Uart_Ipw_AsyncTransmit(u8ChannelId,TxBufPtr->u8DataPtr,TxBufPtr->u16DataLen);
    }

    return ret;
}

uint8_t User_Slip_CreateSlipBuffer(User_Slip_Buffer *RxBufPtr, uint8_t u8data)
{
    static uint8_t u8Data_Last = 0U;

    switch(u8data)
    {
        case USER_SLIP_ESC:
            u8Data_Last = USER_SLIP_ESC;
            break;
        case USER_SLIP_END:
            return USER_SLIP_END_FRAME;
            break;
        default:
            if(u8Data_Last == USER_SLIP_ESC)
            {
                u8Data_Last = 0U;
                if(u8data == USER_SLIP_ESC_END)
                {
                    RxBufPtr->u8DataPtr[RxBufPtr->u16DataLen] = USER_SLIP_END;
                    RxBufPtr->u16DataLen++;
                }
                else if(u8data == USER_SLIP_ESC_ESC)
                {
                    RxBufPtr->u8DataPtr[RxBufPtr->u16DataLen] = USER_SLIP_ESC;
                    RxBufPtr->u16DataLen++;
                }
                else
                {
                    RxBufPtr->u16DataLen = 0U;
                    return USER_SLIP_ERROR_FRAME;
                }
            }
            else
            {
                RxBufPtr->u8DataPtr[RxBufPtr->u16DataLen] = u8data;
                RxBufPtr->u16DataLen++;
            }
            break;
    }

    if (RxBufPtr->u16DataLen > USER_SLIP_BUFFERSIZE)
    {
        RxBufPtr->u16DataLen = 0U;
    }

    return USER_SLIP_NOT_END_FRAME;
}

Std_ReturnType User_Slip_ReceivedFrame (uint8_t u8ChannelId, uint8_t* u8DataPtr, uint16_t* u16DataLenPtr)
{
	uint8_t u8Count;
	uint8_t u8NumberSlipBuffer = 0xFFu;
	uint16_t u16Count;
    uint8_t u8TmpData;
    uint8_t u8SlipReturn;
    uint16_t u16ProtectCount = 0U;
    Std_ReturnType RetVal = E_NOT_OK;
    *u16DataLenPtr = 0U;

    for(u8Count = 0; u8Count < UartConfigPtr->numberChannel; u8Count++)
    {
    	if(UartConfigPtr->ChannelConfig[u8Count].u8HwChannelID == u8ChannelId)
        {
    		u8NumberSlipBuffer = u8Count;
            break;
        }
    }

    if(u8NumberSlipBuffer == 0xFF)
    {
    	return RetVal;
    }

    /* Check frame Slip */
    if(E_NOT_OK == User_Ip_Ipw_FindByte (u8ChannelId, USER_SLIP_END, &u16ProtectCount))
    {
    	if(u16ProtectCount == 0xFFFFu)
    	{
    		User_Ip_Ipw_DeleteRxData(u8ChannelId,u16ProtectCount);
    	}
    	return E_NOT_OK;
    }

    if(u16ProtectCount > USER_SLIP_BUFFERSIZE)
    {
    	User_Ip_Ipw_DeleteRxData(u8ChannelId,u16ProtectCount);
    	return E_NOT_OK;
    }

    while(E_OK == User_Ip_Ipw_ReadByte(u8ChannelId, &u8TmpData))
    {
        u8SlipReturn = User_Slip_CreateSlipBuffer(&User_Slip_RxBuffer[u8NumberSlipBuffer], u8TmpData);
        if (USER_SLIP_END_FRAME == u8SlipReturn)
        {
            if (0U < User_Slip_RxBuffer[u8NumberSlipBuffer].u16DataLen)
            {
                for (u16Count = 0U; u16Count < User_Slip_RxBuffer[u8NumberSlipBuffer].u16DataLen; u16Count++)
                {
                    u8DataPtr[u16Count] = User_Slip_RxBuffer[u8NumberSlipBuffer].u8DataPtr[u16Count];
                }
                *u16DataLenPtr = User_Slip_RxBuffer[u8NumberSlipBuffer].u16DataLen;
                User_Slip_RxBuffer[u8NumberSlipBuffer].u16DataLen = 0U;
                RetVal = E_OK;
                break;
            }
        }
        else if(USER_SLIP_ERROR_FRAME == u8SlipReturn)
        {
        	User_Slip_RxBuffer[u8NumberSlipBuffer].u16DataLen = 0U;
        	return E_NOT_OK;
        }
        else
        {

        }
    }

    return RetVal;
}
