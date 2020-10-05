#include "MyUart.h"
#include "stdint.h"
#include "gpio.h"
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

void Uart_Init()
{
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	  Uart_SetBaudrate();
	  USART1->CR1 = USART_CR1_UE | USART_CR1_TE ;
}
void Uart_Transmit(uint8_t u8Data)
{

	  USART1->DR = u8Data;
}
