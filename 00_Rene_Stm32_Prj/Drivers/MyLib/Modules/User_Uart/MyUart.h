#ifndef __MYUART_H_
#define __MYUART_H_

#include "Usart_Reg.h"
#include "stdint.h"

void Uart_Init(Gst_UartRegType *Channel, uint32_t baudrate);
void Uart_Transmit(Gst_UartRegType *Channel, uint8_t *u8DataPtr, uint32_t u32LengthSize);


#endif /*__MYUART_H_ */
