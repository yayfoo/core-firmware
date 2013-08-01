################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/Protobuf/spark.c 

OBJS += \
./libraries/Protobuf/spark.o 

C_DEPS += \
./libraries/Protobuf/spark.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Protobuf/%.o: ../libraries/Protobuf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -I"../libraries/CMSIS/Include" -I"../libraries/CMSIS/Device/ST/STM32F10x/Include" -I"../libraries/STM32F10x_StdPeriph_Driver/inc" -I"../libraries/STM32_USB-FS-Device_Driver/inc" -I"../libraries/CC3000_Host_Driver" -I"../libraries/Tropicssl/include" -I"../libraries/Protobuf" -I"../inc" -Os -ffunction-sections -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


