#ifndef __USER_UART_SLIP__
#define __USER_UART_SLIP__

#include "Std_Types.h"
#include "User_Uart_Ipw.h"
#include "User_Uart_Cfg.h"

#define USER_SLIP_END                0xC0U
#define USER_SLIP_ESC                0xDBU
#define USER_SLIP_ESC_END            0xDCU
#define USER_SLIP_ESC_ESC            0xDDU

#define USER_SLIP_BUFFERSIZE         (USER_UART_MAX_MESSAGE_LENGTH * 2U)

#define USER_SLIP_END_FRAME          0x00U
#define USER_SLIP_ERROR_FRAME        0x01U
#define USER_SLIP_NOT_END_FRAME      0x02U

typedef struct
{
    uint8_t u8DataPtr[USER_SLIP_BUFFERSIZE];
    uint16_t u16DataLen;
}User_Slip_Buffer;

extern void User_Slip_Init(void);
extern Std_ReturnType User_Slip_SendFrame(uint8_t u8ChannelId, uint8_t *u8DataPtr, uint16_t u16Length);
extern Std_ReturnType User_Slip_ReceivedFrame (uint8_t u8ChannelId, uint8_t* u8DataPtr, uint16_t* u16DataLenPtr);

#endif /* __USER_SLIP__ */
