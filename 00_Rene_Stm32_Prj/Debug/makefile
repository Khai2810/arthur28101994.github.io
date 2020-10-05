################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Drivers/MyLib/Modules/User_Uart/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ReneProj.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ReneProj.list \

OBJCOPY_BIN += \
ReneProj.bin \


# All Target
all: ReneProj.elf secondary-outputs

# Tool invocations
ReneProj.elf: $(OBJS) $(USER_OBJS) E:\00_ReneProj\01_Github\arthur28101994.github.io\00_Rene_Stm32_Prj\STM32F103RETX_FLASH.ld
	arm-none-eabi-gcc -o "ReneProj.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\00_ReneProj\01_Github\arthur28101994.github.io\00_Rene_Stm32_Prj\STM32F103RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ReneProj.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ReneProj.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ReneProj.list"
	@echo 'Finished building: $@'
	@echo ' '

ReneProj.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ReneProj.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
