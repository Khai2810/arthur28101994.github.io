#ifndef __USART_REG_H_
#define __USART_REG_H_
#include "stdint.h"

 typedef struct
  {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
  } Gst_UartRegType;
/* Define number of USART channel that want to use */
#define USART_INSTANCE				0x02

/* define base address of USART */
#define USART_BASEADDR_USART1		(0x40013800U)
#define USART1 						((volatile Gst_UartRegType*) USART_BASEADDR_USART1)

#define USART_BASEADDR_USART2		(0x40004400U)
#define USART2 						((volatile Gst_UartRegType*) USART_BASEADDR_USART2)

#define USART_BASEADDR_USART3		(0x40004800U)
#define USART3 						((volatile Gst_UartRegType*) USART_BASEADDR_USART3)

/* Define array contain base address of usart channel want to use */
//#define USART_BASE_PTRS				{USART1,USART2}


#define USART_RESET_VALUE		0x00000000
#define LENGTH_SHIFT_VALUE		0x01
#define UART_SHIFT(x)	((x & [sobit]) << [vi tri bit tu phai sang trai])

/* define bits of SR register */
#define USART_SR_PE				0x00000001
#define USART_SR_FE				0x00000002
#define USART_SR_NE				0x00000004
#define USART_SR_ORE			0x00000008
#define USART_SR_IDLE			0x00000010
#define USART_SR_RXNE			0x00000020
#define USART_SR_TC				0x00000040
#define USART_SR_LBD			0x00000080
#define USART_SR_CTS			0x00000100

/* define bits of BRR register */
#define USART_BBR_DIV_MANTISSA				0x00000001
#define USART_BBR_FRACTION					0x00000001


/* define bits of CR1 register */
#define USART_BRR_DIV_Mantissa_MASK 0x0000FFF0U
#define USART_BRR_DIV_Fraction_MASK 0x0000000FU
#define USART_CR1_SBK				0x00000001
#define USART_CR1_RWU				0x00000002
#define USART_CR1_RE				0x00000004
#define USART_CR1_TE				0x00000008
#define USART_CR1_IDLEIE			0x00000010
#define USART_CR1_RNXEIE    		0x00000020
#define USART_CR1_TCIE	    		0x00000040
#define USART_CR1_TXEIE	    		0x00000080
#define USART_CR1_PEIE	    		0x00000100
#define USART_CR1_PS	    		0x00000200
#define USART_CR1_PCE	    		0x00000400
#define USART_CR1_WAKE	    		0x00000800
#define USART_CR1_M		    		0x00001000
#define USART_CR1_UE	    		0x00002000


/* define bits of CR2 register */
#define USART_CR2_LBDL				0x00000020
#define USART_CR2_LBDIE				0x00000040
#define USART_CR2_TE				0x00000080
#define USART_CR2_LBCL				0x00000100
#define USART_CR2_CPHA				0x00000200
#define USART_CR2_CPOL				0x00000400
#define USART_CR2_CLKEN				0x00000800
#define USART_CR2_LIEN				0x00004000

/* define bits of CR3 register */
#define USART_CR3_EIE				0x00000001
#define USART_CR3_IREN				0x00000002
#define USART_CR3_IRLP				0x00000004
#define USART_CR3_HDSEL				0x00000008
#define USART_CR3_NACK				0x00000010
#define USART_CR3_SCEN	    		0x00000020
#define USART_CR3_DMAR	    		0x00000040
#define USART_CR3_DMAT	    		0x00000080
#define USART_CR3_RTSE	    		0x00000100
#define USART_CR3_CTSE	    		0x00000200
#define USART_CR3_CTSIE	    		0x00000400

#define UART_SIZE_RING_BUFFER 128U
typedef struct Uart_RingBuffer
{
	uint8_t Uart_Ring_TxBuffer_Channel[UART_SIZE_RING_BUFFER];
	uint8_t Uart_Ring_RxBuffer_Channel[UART_SIZE_RING_BUFFER];
	uint8_t data;
	uint8_t pStart;
	uint8_t pEnd;
}Uart_Ring_Buffer_t;




#endif /*__USART_REG_H_*/
