#include "User_Uart_Cfg.h"

static const User_Uart_HWConfigType User_Uart_HwConfig[USER_UART_NUMBEROFCHANNEL_USED] =
{
    {
    	USER_UART_CHANNEL_USART1,               /* Hw Channel Id */
		USER_UART_SOURCECLOCK_CHANNEL_USART1,    /* Source Clock for HW channel */
		USER_UART_BAUDRATE_CHANNEL_USART1,      /* Baudrate */
        USER_UART_PARITY_NONE,                   /* Parity mode */
        USER_UART_STOP_BIT_1 ,                   /* Stop bit */
		USER_UART_SLIP_ENABLE                    /* Use Slip Protocol*/
    },
    {
    	USER_UART_CHANNEL_USART2,                /* Hw Channel Id */
		USER_UART_SOURCECLOCK_CHANNEL_USART,     /* Source Clock for HW channel */
		USER_UART_BAUDRATE_CHANNEL_USART2,       /* Baudrate */
        USER_UART_PARITY_NONE,                   /* Parity mode */
        USER_UART_STOP_BIT_1 ,                   /* Stop bit */
		USER_UART_SLIP_DISABLE                   /* Use Slip Protocol*/
    }
};

const User_Uart_ConfigType User_Uart_ConfigPtr =
{
    USER_UART_NUMBEROFCHANNEL_USED,
	USER_UART_NUMBEROFHARDWARE_USE,
    (User_Uart_HWConfigType *)User_Uart_HwConfig

};

