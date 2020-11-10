#ifndef __USER_UART_TYPES__
#define __USER_UART_TYPES__


typedef enum __User_Uart_StopBitCount_t
{
    USER_UART_STOP_BIT_1 = 0x0U,
    USER_UART_STOP_BIT_2 = 0x2U
} User_Uart_StopBitCount_t;

typedef enum __User_Uart_ParityMode_t
{
    USER_UART_PARITY_NONE    = 0x0U,
    USER_UART_PARITY_EVEN    = 0x1U,
    USER_UART_PARITY_ODD     = 0x2U
} User_Uart_ParityMode_t;

typedef enum __User_Uart_SlipStatus_t
{
    USER_UART_SLIP_ENABLE   = 0x0U,
	USER_UART_SLIP_DISABLE  = 0x1U,
} User_Uart_SlipStatus_t;

typedef struct __User_Uart_ChannelConfigType
{
    uint8_t                      u8HwChannelID;
    uint32_t                     u32SourceClock;
    uint32_t                     u32Baudrate;
    User_Uart_ParityMode_t       ParityMode;
    User_Uart_StopBitCount_t     StopBitCount;
    User_Uart_SlipStatus_t       SlipStatus;
} User_Uart_HWConfigType;

typedef struct
{
    uint8_t numberChannel;
    uint8_t numberHardware;
    User_Uart_HWConfigType *ChannelConfig;
} User_Uart_ConfigType;



#endif /* __USER_UART_TYPES__ */
