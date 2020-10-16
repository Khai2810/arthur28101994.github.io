#ifndef __MYUART_H_
#define __MYUART_H_

#include "Usart_Reg.h"
#include "stdint.h"

void Uart_Init(Gst_UartRegType *Channel);
void Uart_Transmit(Gst_UartRegType *Channel, uint8_t* u8DataPtr, uint8_t u8LengthSize);


#endif /*__MYUART_H_ */
