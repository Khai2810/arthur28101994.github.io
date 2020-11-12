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

	/* Enable TX/RX */
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
	/* Nothing to do with Channel */
	(void)Channel;

	/* Free Tx/Rx buffer */
	queueRelease(tx_queue_buffer);
	queueRelease(rx_queue_buffer);

	/* Disable Interrupt*/
	HAL_NVIC_DisableIRQ(USART1_IRQn);
}

void Uart_Transmit(Gst_UartRegType *Channel, uint8_t *u8DataPtr, uint32_t u32LengthSize)
{
	int32_t len = u32LengthSize;

	/* Disable Tx interrupt */
	Channel->CR1 &= (uint32_t)(~USART_CR1_TXEIE);
	while(len > 0)
	{
		while(len > 0 && enQueue(tx_queue_buffer, *u8DataPtr++))
			len--;
		/* Enable Tx interrupt */
		Channel->CR1 |= (uint32_t)USART_CR1_TXEIE;
	}
}

void Uart_Receive(Gst_UartRegType *Channel, uint8_t *u8DataPtr, uint32_t u32LengthSize)
{

	char byte;

	/* Enable Rx interrupt */
	Channel->CR1 |= (uint32_t)USART_CR1_RXNEIE;

	while (u32LengthSize && deQueue(rx_queue_buffer, &byte)) {
		u32LengthSize--;
		*(u8DataPtr++) = byte;
	};
}

void USART1_IRQHandler(void)
{
	uint8_t byte;

	/* Transmiting */
	if ((USART1->SR & USART_SR_TXE) == USART_SR_TXE)
		/* Write data to DR register if data is popped from Queue successfully */
	{
		if (deQueue(tx_queue_buffer, &byte))
			USART1->DR = byte;
			/* Disable Tx interrupt */
		else
			USART1->CR1 &= (uint32_t)(~USART_CR1_TXEIE);
	}

	/* Receiving */
//	if ((USART1->SR >> 5)) {
//		enQueue(rx_queue_buffer, (char)USART1->DR);
//	}

}
