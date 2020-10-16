################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MyLib/Modules/User_Uart/MyUart.c 

OBJS += \
./Drivers/MyLib/Modules/User_Uart/MyUart.o 

C_DEPS += \
./Drivers/MyLib/Modules/User_Uart/MyUart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MyLib/Modules/User_Uart/MyUart.o: ../Drivers/MyLib/Modules/User_Uart/MyUart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xE -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"E:/00_ReneProj/01_Github/arthur28101994.github.io/00_Rene_Stm32_Prj/Drivers/MyLib/Modules/User_Uart/ip/usart" -I"E:/00_ReneProj/01_Github/arthur28101994.github.io/00_Rene_Stm32_Prj/Drivers/MyLib/Modules/User_Uart" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/MyLib/Modules/User_Uart/MyUart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

