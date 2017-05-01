################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_enet.c \
../drivers/fsl_flash.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_i2c_freertos.c \
../drivers/fsl_rtc.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c \
../drivers/fsl_uart_freertos.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_enet.o \
./drivers/fsl_flash.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_i2c_freertos.o \
./drivers/fsl_rtc.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o \
./drivers/fsl_uart_freertos.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_enet.d \
./drivers/fsl_flash.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_i2c_freertos.d \
./drivers/fsl_rtc.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d \
./drivers/fsl_uart_freertos.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DCPU_MK64FN1M0VDC12_cm4 -DCPU_MK64FN1M0VDC12 -D__REDLIB__ -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\source" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\startup" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\drivers" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\frdmk64f" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\utilities" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\CMSIS" -I"E:\workspace\McuXpresso\MK64FN1M0xxx12_Center\freertos" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


