#include "MyUart.h"
#include "stdint.h"
#include "gpio.h"
#include "Queue.h"


Uart_Ring_Buffer_t* BufferUart1;

queue_buffer_t *tx_queue_buffer;
queue_buffer_t *rx_queue_buffer;

void Uart_Write_Buffer(Gst_UartRegType *Channel, const uint8_t* pu8Data, uint8_t u8LengthSize)
{
	uint8_t LengthAvailable;
	uint8_t count;

	//~ if(BufferUart1->pStart > BufferUart1->pEnd)
	//~ {
		//~ LengthAvailable = BufferUart1->pStart - BufferUart1->pEnd;
	//~ }
	//~ else
	//~ {
		//~ LengthAvailable = (UART_SIZE_RING_BUFFER - BufferUart1->pEnd) + BufferUart1->pStart;
	//~ }
	//~ if (LengthAvailable >= u8LengthSize )
	//~ {
		//~ for (count = 0; count < u8LengthSize; count++)
		//~ {
			//~ BufferUart1->Uart_Ring_TxBuffer_Channel[BufferUart1->pEnd] = *pu8Data;
			//~ BufferUart1->pEnd = (BufferUart1->pEnd + 1) & (UART_SIZE_RING_BUFFER - 1);
			//~ pu8Data++;
		//~ }
	//~ }
	
	for (count = 0; count < u8LengthSize; count++) {
		enQueue(tx_queue_buffer, *(pu8Data++));
	}
	
	Channel->CR1 = USART_CR1_TXEIE ;
}

void Uart_SetBaudrate()
{
	  /*Calculate Baudrate */
	  /* USARTDIV = DIV_Mantissa + (DIV_Fraction / 16) */
	  /* Tx/ Rx baud =
	  legend: fCK - Input clock to the peripheral (PCLK1 for USART2, 3, 4, 5 or PCLK2 for USART1)
	  fCK/(16*USARTDIV) */
	  uint32_t FCK = 72000000;
	  uint32_t DIV_Mantissa;
	  uint32_t DIV_Fraction;
	  uint32_t  Baudrate = 9600;
	  DIV_Mantissa = FCK / (Baudrate * 16);
	  DIV_Fraction = (FCK / Baudrate) % 16;
	  USART1->BRR = (DIV_Mantissa << 4) & USART_BRR_DIV_Mantissa_MASK;
	  USART1->BRR |= DIV_Fraction & USART_BRR_DIV_Fraction_MASK;
}

void Uart_Init(Gst_UartRegType *Channel)
{
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	  Uart_SetBaudrate();
	  Channel->CR1 = USART_CR1_UE | USART_CR1_TE ;
	  
	  tx_queue_buffer = queueCreate(128);
	  rx_queue_buffer = queueCreate(128);
}

void Uart_DeInit(Gst_UartRegType *Channel)
{
	(void)Channel;
	
	queueRelease(tx_queue_buffer);
	queueRelease(rx_queue_buffer);
}

void Uart_Transmit(Gst_UartRegType *Channel, uint8_t* u8DataPtr, uint8_t u8LengthSize)
{
	Uart_Write_Buffer(Channel, u8DataPtr, u8LengthSize);
}

void USART1_IRQHandler(void)
{
	//~ USART1->DR = BufferUart1->Uart_Ring_TxBuffer_Channel[BufferUart1->pStart];
	//~ if (++BufferUart1->pStart >= UART_SIZE_RING_BUFFER)
	//~ {
		//~ BufferUart1->pStart = 0;
	//~ }
	
	char c;
	deQueue(tx_queue_buffer, &c);
	USART1->DR = c;
}

