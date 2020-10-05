#ifndef __MYUART_H_
#define __MYUART_H_

#include "Usart_Reg.h"
#include "stdint.h"

void Uart_Init();
void Uart_Transmit(uint8_t u8Data);


#endif /*__MYUART_H_ */
