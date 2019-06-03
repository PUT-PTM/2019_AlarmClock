################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/._i2c-lcd.c \
../Src/._sd3231.c \
../Src/._system_stm32f4xx.c \
../Src/Bell.c \
../Src/Black_Sails_OST.c \
../Src/IndianaJones.c \
../Src/i2c-lcd.c \
../Src/main.c \
../Src/sd3231.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/._i2c-lcd.o \
./Src/._sd3231.o \
./Src/._system_stm32f4xx.o \
./Src/Bell.o \
./Src/Black_Sails_OST.o \
./Src/IndianaJones.o \
./Src/i2c-lcd.o \
./Src/main.o \
./Src/sd3231.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/._i2c-lcd.d \
./Src/._sd3231.d \
./Src/._system_stm32f4xx.d \
./Src/Bell.d \
./Src/Black_Sails_OST.d \
./Src/IndianaJones.d \
./Src/i2c-lcd.d \
./Src/main.d \
./Src/sd3231.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -I"C:/Users/adudz/Desktop/LCDDobre/Inc" -I"C:/Users/adudz/Desktop/LCDDobre/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/adudz/Desktop/LCDDobre/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/adudz/Desktop/LCDDobre/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/adudz/Desktop/LCDDobre/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


