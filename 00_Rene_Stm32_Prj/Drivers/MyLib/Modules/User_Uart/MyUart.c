#include "MyUart.h"
#include "stdint.h"
#include "gpio.h"
#include "Queue.h"

queue_buffer_t *tx_queue_buffer;
queue_buffer_t *rx_queue_buffer;

void Uart_SetBaudrate(Gst_UartRegType *Channel, uint32_t baudrate)
{
	/*Calculate Baudrate */
	/* USARTDIV = DIV_Mantissa + (DIV_Fraction / 16) */
	/* Tx/ Rx baud =
	legend: fCK - Input clock to the peripheral (PCLK1 for USART2, 3, 4, 5 or PCLK2 for USART1)
	fCK/(16*USARTDIV) */

	uint32_t FCK = 72000000;
	uint32_t DIV_Mantissa;
	uint32_t DIV_Fraction;

	DIV_Mantissa = FCK / (baudrate * 16);
	DIV_Fraction = (FCK / baudrate) % 16;
	Channel->BRR = ((DIV_Mantissa << 4) & USART_BRR_DIV_Mantissa_MASK) |
				(DIV_Fraction & USART_BRR_DIV_Fraction_MASK);
}


void Uart_Init(Gst_UartRegType *Channel, uint32_t baudrate)
{
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	/* Setting baudrate */
	Uart_SetBaudrate(Channel, baudrate);

	/* Enable TX */
	Channel->CR1 = USART_CR1_UE | USART_CR1_TE ;

	/* Init Tx/Rx buffer */
	tx_queue_buffer = queueCreate(128);
	rx_queue_buffer = queueCreate(128);

	/* Enable Interrupt*/
	HAL_NVIC_SetPriority(USART1_IRQn, 5, 0u);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
}


void Uart_DeInit(Gst_UartRegType *Channel)
{
	/* Do nothing with Channel */
	(void)Channel;

	/* Free Tx/Rx buffer */
	queueRelease(tx_queue_buffer);
	queueRelease(rx_queue_buffer);

	/* Disable Interrupt*/
	HAL_NVIC_DisableIRQ(USART1_IRQn);
}


void Uart_Transmit(Gst_UartRegType *Channel, uint8_t *u8DataPtr, uint32_t u32LengthSize)
{
	uint32_t LengthAvailable = u32LengthSize;

	while ((LengthAvailable--) && (!enQueue(tx_queue_buffer, *(pu8Data++))))
		/* Do nothing here */;

	Channel->CR1 |= (uint32_t)USART_CR1_TXEIE;
}


void USART1_IRQHandler(void)
{
	uint8_t byte;

	/* Disable Tx interrupt */
	USART1->CR1 &= (uint32_t)(~USART_CR1_TXEIE);

	/* TXE bit as 1 */
	if ((USART1->SR >> 7))
		/* Write data to DR register if data is popped from Queue successfully */
		if (deQueue(tx_queue_buffer, &byte))
			USRT1->DR = byte;
}

