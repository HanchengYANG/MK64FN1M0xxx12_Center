################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/I2C/DS3231/DS3231.c 

OBJS += \
./source/I2C/DS3231/DS3231.o 

C_DEPS += \
./source/I2C/DS3231/DS3231.d 


# Each subdirectory must supply rules for building sources it contributes
source/I2C/DS3231/%.o: ../source/I2C/DS3231/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DCPU_MK64FN1M0VDC12_cm4 -DCPU_MK64FN1M0VDC12 -D__REDLIB__ -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\source" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\startup" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\drivers" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\frdmk64f" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\utilities" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\CMSIS" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\freertos" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


