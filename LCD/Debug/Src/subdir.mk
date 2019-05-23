################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/audio.c \
../Src/audio2.c \
../Src/i2c-lcd.c \
../Src/main.c \
../Src/sd3231.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/audio.o \
./Src/audio2.o \
./Src/i2c-lcd.o \
./Src/main.o \
./Src/sd3231.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/audio.d \
./Src/audio2.d \
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
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/stanislawkucznerowicz/Documents/Ptm/LCD/Inc" -I"/Users/stanislawkucznerowicz/Documents/Ptm/LCD/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/stanislawkucznerowicz/Documents/Ptm/LCD/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/stanislawkucznerowicz/Documents/Ptm/LCD/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/stanislawkucznerowicz/Documents/Ptm/LCD/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


