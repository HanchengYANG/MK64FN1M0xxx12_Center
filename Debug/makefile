################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/Misc/subdir.mk
-include source/I2C/MCP23016/subdir.mk
-include source/I2C/HAL/subdir.mk
-include source/I2C/DS3231/subdir.mk
-include source/App/subdir.mk
-include source/subdir.mk
-include freertos/subdir.mk
-include frdmk64f/subdir.mk
-include drivers/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MK64FN1M0xxx12_Center.axf

# Tool invocations
MK64FN1M0xxx12_Center.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="MK64FN1M0xxx12_Center.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T MK64FN1M0xxx12_Center_Debug.ld -o "MK64FN1M0xxx12_Center.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) MK64FN1M0xxx12_Center.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "MK64FN1M0xxx12_Center.axf"; # arm-none-eabi-objcopy -v -O binary "MK64FN1M0xxx12_Center.axf" "MK64FN1M0xxx12_Center.bin" ; # checksum -p MK64FN1M0xxx12 -d "MK64FN1M0xxx12_Center.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
