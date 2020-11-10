#ifndef __USER_IP_USART_TYPES__
#define __USER_IP_USART_TYPES__


#define USER_IP_USART_SIZE_RINGBUFF       128u



typedef enum __User_Ip_Usart_BufferStatus_t
{
    USART_BUFFER_UNLOCK  = 0x0U,
	USART_BUFFER_LOCK    = 0x1U,
	USART_BUFFER_FULL    = 0x2U
} User_Ip_Usart_BufferStatus_t;

typedef struct
{
    volatile uint8_t User_Ip_Usart_RingTxBufferChannel[USER_IP_USART_SIZE_RINGBUFF];
    volatile uint8_t User_Ip_Usart_RingRxBufferChannel[USER_IP_USART_SIZE_RINGBUFF];
    volatile uint16_t TxTail;
    volatile uint16_t TxHead;
    volatile uint16_t RxTail;
    volatile uint16_t RxHead;
    User_Ip_Usart_BufferStatus_t Status;
} User_Ip_Usart_RingBuffer_t;





#endif /* __USER_IP_USART_TYPES__ */
