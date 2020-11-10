################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ITC/Module/User_Uart/cfg/User_Uart_Cfg.c 

OBJS += \
./Drivers/ITC/Module/User_Uart/cfg/User_Uart_Cfg.o 

C_DEPS += \
./Drivers/ITC/Module/User_Uart/cfg/User_Uart_Cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ITC/Module/User_Uart/cfg/User_Uart_Cfg.o: ../Drivers/ITC/Module/User_Uart/cfg/User_Uart_Cfg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/ITC/Module/User_Uart -I../Drivers/ITC/Module/User_Uart/cfg -I../Drivers/ITC/Module/User_Uart/ip/usart -I../Drivers/ITC/Module/User_Uart/protocol/slip -I../Drivers/ITC/Mid/base -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/ITC/Module/User_Uart/cfg/User_Uart_Cfg.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

