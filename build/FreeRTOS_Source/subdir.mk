
# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS_Source/list.c \
../FreeRTOS_Source/queue.c \
../FreeRTOS_Source/tasks.c \
../FreeRTOS_Source/timers.c 

OBJS += \
./FreeRTOS_Source/list.o \
./FreeRTOS_Source/queue.o \
./FreeRTOS_Source/tasks.o \
./FreeRTOS_Source/timers.o 

C_DEPS += \
./FreeRTOS_Source/list.d \
./FreeRTOS_Source/queue.d \
./FreeRTOS_Source/tasks.d \
./FreeRTOS_Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_Source/%.o: ../FreeRTOS_Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM GCC C Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -DDFU_BUILD_ENABLE -I"../../core-common-lib/CMSIS/Include" -I"../../core-common-lib/CMSIS/Device/ST/STM32F10x/Include" -I"../../core-common-lib/STM32F10x_StdPeriph_Driver/inc" -I"../../core-common-lib/STM32_USB-FS-Device_Driver/inc" -I"../../core-common-lib/CC3000_Host_Driver" -I"../../core-common-lib/SPARK_Firmware_Driver/inc" -I"../../core-communication-lib/lib/tropicssl/include" -I"../../core-communication-lib/src" -I"../inc" -I"../FreeRTOS_Source/include" -I"../FreeRTOS_Source/portable/GCC/ARM_CM3" -Os -ffunction-sections -Wall -Werror -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


