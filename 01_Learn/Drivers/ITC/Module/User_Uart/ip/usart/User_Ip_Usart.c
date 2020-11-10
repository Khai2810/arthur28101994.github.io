#include "User_Ip_Usart.h"
#include "User_Ip_Usart_Register.h"

#define USER_IP_USART_MIN_RANGEBAUDRATE       (16u)

static User_Ip_Usart_RingBuffer_t Buffer_Usart1Channel;
static User_Ip_Usart_RingBuffer_t Buffer_Usart2Channel;
static User_Ip_Usart_RingBuffer_t Buffer_Usart3Channel;
static User_Ip_Usart_Type * const User_Ip_Usart_BaseAddress[USER_IP_USART_INSTANCE_COUNT] = USER_IP_USART_BASE_PTRS;
static User_Ip_Usart_RingBuffer_t * Buffer_Ptr_Arr[USER_IP_USART_INSTANCE_COUNT] = {&Buffer_Usart1Channel, &Buffer_Usart2Channel, &Buffer_Usart3Channel};
static User_UsartIRQn_Type User_Usart_IRQn[USER_IP_USART_INSTANCE_COUNT] = USER_IP_USART_RXTX_IRQS;


static User_Ip_Usart_RingBuffer_t *User_Ip_Usart_GetBuffer(uint8_t u8ChannelId);

static Std_ReturnType User_Ip_Usart_SetBaudrate (User_Ip_Usart_Type * HwChannel, uint32_t UsartSourceClock, uint32_t baudrate)
{

    uint16_t DIV_Mantissa = 0;
    uint16_t DIV_Fraction = 0;
    Std_ReturnType ret = E_NOT_OK;

    /* In case of oversampling by 16 */
    DIV_Mantissa = UsartSourceClock / (16 * baudrate);
    DIV_Fraction = (UsartSourceClock / (baudrate)) % 16 ;

    HwChannel->BRR = (DIV_Mantissa << 4) & USER_IP_USART_BRR_DIV_Mantissa_MASK;
    HwChannel->BRR |= DIV_Fraction & USER_IP_USART_BRR_DIV_Fraction_MASK;

    ret = E_OK;
    return ret;
}

static void User_Ip_Usart_SetParityMode(User_Ip_Usart_Type *HwChannel, User_Uart_ParityMode_t parityMode)
{
    uint8_t u8ParityMode = 0;

    if (parityMode == USER_UART_PARITY_NONE)
    {
        HwChannel->CR1 &= ~USER_IP_USART_CR1_PS_MASK;
    }
    else
    {
        u8ParityMode = parityMode - 1u;
        HwChannel->CR1 |= USER_IP_USART_CR1_PS_MASK;
        HwChannel->CR1 |= u8ParityMode << USER_IP_USART_CR1_PCE_SHIFT;
    }
}

static void User_Ip_Usart_SetStopBitCount(User_Ip_Usart_Type *HwChannel, User_Uart_StopBitCount_t stopBitCount)
{
    HwChannel->CR2 &= ~USER_IP_USART_CR2_STOP_MASK;
    HwChannel->CR2 |= ((stopBitCount << USER_IP_USART_CR2_STOP_SHIFT) & USER_IP_USART_CR2_STOP_MASK);
}

void User_Ip_Usart_DeInit(User_Ip_Usart_Type *HwChannel)
{
    uint16_t u16countInstance = 0;
    uint16_t u16countByte = 0;
    User_Ip_Usart_RingBuffer_t * BufferChannel;

    HwChannel->CR1 = USER_IP_USART_RESET_VALUE;
    HwChannel->CR2 = USER_IP_USART_RESET_VALUE;
    HwChannel->CR3 = USER_IP_USART_RESET_VALUE;
    HwChannel->BRR = USER_IP_USART_RESET_VALUE;

    for (u16countInstance = 0; u16countInstance < USER_IP_USART_INSTANCE_COUNT; u16countInstance++)
    {
        BufferChannel = Buffer_Ptr_Arr[u16countInstance];
        BufferChannel->RxHead = 0;
        BufferChannel->RxTail = 0;
        BufferChannel->TxHead = 0;
        BufferChannel->TxTail = 0;
        BufferChannel->Status = USART_BUFFER_UNLOCK;

        for (u16countByte = 0; u16countByte < USER_IP_USART_SIZE_RINGBUFF; u16countByte++)
        {
            BufferChannel->User_Ip_Usart_RingRxBufferChannel[u16countByte] = 0x00u;
            BufferChannel->User_Ip_Usart_RingTxBufferChannel[u16countByte] = 0x00u;
        }
    }
}


void User_Ip_Usart_Init(User_Uart_HWConfigType *HwConfig)
{
    uint8_t u8ChannelId = HwConfig->u8HwChannelID;
    User_Ip_Usart_Type *Usart = User_Ip_Usart_BaseAddress[u8ChannelId];
   // uint8_t u8Temp;

    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();


    User_Ip_Usart_DeInit (Usart);
    Usart->CR1 &= ~USER_IP_USART_CR1_TE_MASK;
    Usart->CR1 &= ~USER_IP_USART_CR1_RE_MASK;

    User_Ip_Usart_SetBaudrate (Usart, HwConfig->u32SourceClock, HwConfig->u32Baudrate);
    User_Ip_Usart_SetParityMode(Usart, HwConfig->ParityMode);
    User_Ip_Usart_SetStopBitCount(Usart, HwConfig->StopBitCount);

    /* Clear RXNE flag */
   // u8Temp = Usart->DR;
    Usart->CR3 |= USER_IP_USART_CR3_EIE_MASK;
    Usart->CR1 |= ( USER_IP_USART_CR1_RXNEIE_MASK |\
                    USER_IP_USART_CR1_TE_MASK |\
                    USER_IP_USART_CR1_RE_MASK |\
                    USER_IP_USART_CR1_UE_MASK );

    /* Enable Interrupt*/
    HAL_NVIC_SetPriority(User_Usart_IRQn[u8ChannelId], USER_IP_USART_PRIORITY, 0u);
    HAL_NVIC_EnableIRQ(User_Usart_IRQn[u8ChannelId]);
}

static User_Ip_Usart_RingBuffer_t *User_Ip_Usart_GetBuffer (uint8_t u8ChannelId)
{
    User_Ip_Usart_RingBuffer_t *BufferChannel;

    if(u8ChannelId == USER_IP_USART_CHANNELID_1)
    {
        BufferChannel = &Buffer_Usart1Channel;
    }
    else if(u8ChannelId == USER_IP_USART_CHANNELID_2)
    {
        BufferChannel = &Buffer_Usart2Channel;
    }
    else if(u8ChannelId == USER_IP_USART_CHANNELID_3)
    {
        BufferChannel = &Buffer_Usart3Channel;
    }
    else
    {
        BufferChannel = NULL;
    }

    return BufferChannel;
}

Std_ReturnType User_Ip_Usart_FindByte(uint8_t u8ChannelId, uint8_t u8ByteF,uint16_t *u16Local)
{
    uint16_t u16Count = 0u;
    uint16_t u16ProtectCount = 0U;
    User_Ip_Usart_RingBuffer_t *BufferChannel;

    BufferChannel = User_Ip_Usart_GetBuffer(u8ChannelId);
    if(BufferChannel == NULL)
    {
        return E_NOT_OK;
    }

    u16Count = BufferChannel->RxHead;

    while (u16Count != BufferChannel->RxTail)
    {
        if(++ u16Count == USER_IP_USART_SIZE_RINGBUFF)
        {
            u16Count = 0;
        }

        u16ProtectCount ++;

        if(BufferChannel->User_Ip_Usart_RingRxBufferChannel[u16Count] == u8ByteF)
        {
            *u16Local = u16ProtectCount;
            return E_OK;
        }
    }

    if(BufferChannel->RxHead == BufferChannel->RxTail + 1)
    {
    	*u16Local = 0xFFFF;
    }

    return E_NOT_OK;
}

Std_ReturnType User_Ip_Usart_DeleteRxData (uint8_t u8ChannelId, uint16_t u16DlSize)
{
    uint16_t u16DataLen = 0u;
    User_Ip_Usart_RingBuffer_t *BufferChannel;

    BufferChannel = User_Ip_Usart_GetBuffer(u8ChannelId);
    if (BufferChannel->RxTail > BufferChannel->RxHead)
    {
        u16DataLen = BufferChannel->RxTail - BufferChannel->RxHead;
    }
    else if ( BufferChannel->RxTail < BufferChannel->RxHead)
    {
        u16DataLen = (USER_IP_USART_SIZE_RINGBUFF - BufferChannel->RxHead) + BufferChannel->RxTail;
    }
    else
    {
        return E_NOT_OK;
    }

    if (u16DataLen <= u16DlSize)
    {
        BufferChannel->RxHead = BufferChannel->RxTail;
    }
    else
    {
        BufferChannel->RxHead = (BufferChannel->RxHead + u16DlSize) & (USER_IP_USART_SIZE_RINGBUFF - 1);
    }

    return E_OK;
}

Std_ReturnType User_Ip_Usart_ReadByte(uint8_t u8ChannelId, uint8_t *u8Data)
{
    User_Ip_Usart_RingBuffer_t * BufferChannel;

    BufferChannel = User_Ip_Usart_GetBuffer(u8ChannelId);
    if(BufferChannel == NULL)
    {
        return E_NOT_OK;
    }

    if (BufferChannel->RxTail != BufferChannel->RxHead)
    {
        *u8Data = BufferChannel->User_Ip_Usart_RingRxBufferChannel[BufferChannel->RxHead];
        BufferChannel->RxHead = (BufferChannel->RxHead + 1) & (USER_IP_USART_SIZE_RINGBUFF - 1);
    }
    else
    {
    }

    return E_OK;
}

static inline void User_Ip_Usart_PutChar (User_Ip_Usart_Type *Usart_channel, uint8_t u8Data)
{
    Usart_channel->DR = u8Data;
}

static inline void User_Ip_Usart_StartAsyncTransmit (User_Ip_Usart_Type *Usart_channel)
{
    Usart_channel->CR1 |= USER_IP_USART_CR1_TXEIE_MASK;
}

static inline void User_Ip_Usart_StopAsyncTransmit (User_Ip_Usart_Type *Usart_channel)
{
    Usart_channel->CR1 &= ~USER_IP_USART_CR1_TXEIE_MASK;
}


Std_ReturnType User_Ip_Usart_WriteBuffer (uint8_t u8ChannelId, const uint8_t *u8DataPtr, int16_t u16DataLen)
{
    Std_ReturnType ret = E_NOT_OK;
    uint16_t u16AvailableLen = 0;
    uint16_t u16CountLen = 0;
    User_Ip_Usart_RingBuffer_t * BufferChannel;

    BufferChannel = User_Ip_Usart_GetBuffer (u8ChannelId);
    if (BufferChannel == NULL)
    {
        return E_NOT_OK;
    }

    if (u8DataPtr == NULL || u16DataLen == 0u)
    {
        return E_NOT_OK;
    }

    if (BufferChannel->Status == USART_BUFFER_UNLOCK)
    {
    	BufferChannel->Status = USART_BUFFER_LOCK;
        if (BufferChannel->TxHead > BufferChannel->TxTail)
        {
            u16AvailableLen = BufferChannel->TxHead - BufferChannel->TxTail;
        }
        else
        {
            u16AvailableLen = (USER_IP_USART_SIZE_RINGBUFF - BufferChannel->TxTail) + BufferChannel->TxHead;
        }

        if (u16AvailableLen >= u16DataLen)
        {
            for (u16CountLen = 0; u16CountLen < u16DataLen; u16CountLen++)
            {
                BufferChannel->User_Ip_Usart_RingTxBufferChannel[BufferChannel->TxTail] = *u8DataPtr;
                if(++ BufferChannel->TxTail >= USER_IP_USART_SIZE_RINGBUFF)
                {
                	BufferChannel->TxTail = 0;
                }
                u8DataPtr ++;
            }
            BufferChannel->Status = USART_BUFFER_UNLOCK;
            User_Ip_Usart_StartAsyncTransmit (User_Ip_Usart_BaseAddress[u8ChannelId]);
            ret = E_OK;
        }
    }

    return ret;
}


static inline void User_Ip_Usart_TransmitBuffer(uint8_t u8ChannelId)
{
    User_Ip_Usart_RingBuffer_t *BufferChannel;
    User_Ip_Usart_Type *HwChannel = User_Ip_Usart_BaseAddress[u8ChannelId];

    BufferChannel = User_Ip_Usart_GetBuffer(u8ChannelId);
    if(BufferChannel == NULL)
    {
        return;
    }

    if(BufferChannel->TxTail != BufferChannel->TxHead)
    {
        User_Ip_Usart_PutChar (HwChannel, BufferChannel->User_Ip_Usart_RingTxBufferChannel[BufferChannel->TxHead]);
        if(++ BufferChannel->TxHead >= USER_IP_USART_SIZE_RINGBUFF)
        {
        	BufferChannel->TxHead = 0;
        }
    }
    else
    {
        User_Ip_Usart_StopAsyncTransmit(HwChannel);
    }
}

Std_ReturnType User_Ip_Usart_ReadBuffer(uint8_t u8ChannelId, uint8_t *u8data, uint16_t u16length, int16_t *i16remain)
{
    uint16_t u16Count = 0u;
    User_Ip_Usart_RingBuffer_t * BufferChannel;

    BufferChannel = User_Ip_Usart_GetBuffer(u8ChannelId);
    if(BufferChannel == NULL)
    {
        return E_NOT_OK;
    }

    if(BufferChannel->RxHead == BufferChannel->RxTail)
	{
		return E_NOT_OK;
	}

    for (u16Count = 0; u16Count < u16length; u16Count++)
    {
        if (BufferChannel->RxHead != BufferChannel->RxTail)
        {
            *u8data = BufferChannel->User_Ip_Usart_RingRxBufferChannel[BufferChannel->RxHead];
            if(++ BufferChannel->RxHead >= USER_IP_USART_SIZE_RINGBUFF)
            {
            	BufferChannel->RxHead = 0;
            }
            u8data ++;
        }
        else
        {
            *i16remain = u16Count - u16length;
            return E_OK;
        }
    }

    if(BufferChannel->RxTail >= BufferChannel->RxHead)
    {
        *i16remain = BufferChannel->RxTail - BufferChannel->RxHead;
    }
    else
    {
        *i16remain = (USER_IP_USART_SIZE_RINGBUFF - BufferChannel->RxHead) + BufferChannel->RxTail;
    }

    return E_OK;
}

static inline uint8_t User_Ip_Usart_GetChar (User_Ip_Usart_Type * Usart_channel)
{
    return (Usart_channel->DR);
}

static void User_Ip_Usart_ReceiveBuffer(uint8_t u8ChannelId, uint8_t u8Data)
{
    User_Ip_Usart_RingBuffer_t *BufferChannel;

    BufferChannel = User_Ip_Usart_GetBuffer(u8ChannelId);
    if(BufferChannel == NULL)
    {
        return;
    }

    if(BufferChannel->RxTail != BufferChannel->RxHead - 1u)
    {
    	BufferChannel->User_Ip_Usart_RingRxBufferChannel[BufferChannel->RxTail] = u8Data;
    	if(++ BufferChannel->RxTail >= USER_IP_USART_SIZE_RINGBUFF)
    	{
    		BufferChannel->RxTail = 0;
    	}
    }

    if(BufferChannel->RxTail == BufferChannel->RxHead)
    {
        if(BufferChannel->RxHead == 0U)
        {
            BufferChannel->RxTail = USER_IP_USART_SIZE_RINGBUFF - 1U;
        }
        else
        {
        	BufferChannel->RxTail -= 1;
        }
    }
}

static void User_Ip_Usart_IrqHandler(uint8_t u8ChannelId)
{
    uint8_t Byte_Receive = 0u;
    User_Ip_Usart_Type *HwChannel = User_Ip_Usart_BaseAddress[u8ChannelId];

    if((HwChannel->SR & USER_IP_USART_SR_TXE_MASK) == USER_IP_USART_SR_TXE_MASK)
    {
        User_Ip_Usart_TransmitBuffer(u8ChannelId);
    }

    if((HwChannel->SR & USER_IP_USART_SR_RXNE_MASK) == USER_IP_USART_SR_RXNE_MASK)
    {
    	Byte_Receive = User_Ip_Usart_GetChar(HwChannel);
        User_Ip_Usart_ReceiveBuffer(u8ChannelId,Byte_Receive);
    }

    if((HwChannel->SR & USER_IP_USART_SR_PE_MASK) == USER_IP_USART_SR_PE_MASK)
    {
        /*TODO*/

    }

    if((HwChannel->SR & USER_IP_USART_SR_FE_MASK) == USER_IP_USART_SR_FE_MASK)
    {
        /*TODO*/

    }

    if((HwChannel->SR & USER_IP_USART_SR_ORE_MASK) == USER_IP_USART_SR_ORE_MASK)
    {
        /*TODO*/

        User_Ip_Usart_GetChar(HwChannel);
    }
}

void USART1_IRQHandler(void)
{
    User_Ip_Usart_IrqHandler(USER_IP_USART_CHANNELID_1);
}

void USART2_IRQHandler(void)
{
    User_Ip_Usart_IrqHandler(USER_IP_USART_CHANNELID_2);
}

void USART3_IRQHandler(void)
{
    User_Ip_Usart_IrqHandler(USER_IP_USART_CHANNELID_3);
}
