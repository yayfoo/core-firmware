
# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../protobuf/api/chunk.c \
../protobuf/api/chunk_received.c \
../protobuf/api/event.c \
../protobuf/api/function_call.c \
../protobuf/api/function_return.c \
../protobuf/api/general.c \
../protobuf/api/hello.c \
../protobuf/api/ignored.c \
../protobuf/api/key_change.c \
../protobuf/api/update_begin.c \
../protobuf/api/update_done.c \
../protobuf/api/update_ready.c \
../protobuf/api/variable_request.c \
../protobuf/api/variable_value.c 

OBJS += \
./protobuf/api/chunk.o \
./protobuf/api/chunk_received.o \
./protobuf/api/event.o \
./protobuf/api/function_call.o \
./protobuf/api/function_return.o \
./protobuf/api/general.o \
./protobuf/api/hello.o \
./protobuf/api/ignored.o \
./protobuf/api/key_change.o \
./protobuf/api/update_begin.o \
./protobuf/api/update_done.o \
./protobuf/api/update_ready.o \
./protobuf/api/variable_request.o \
./protobuf/api/variable_value.o 

C_DEPS += \
./protobuf/api/chunk.d \
./protobuf/api/chunk_received.d \
./protobuf/api/event.d \
./protobuf/api/function_call.d \
./protobuf/api/function_return.d \
./protobuf/api/general.d \
./protobuf/api/hello.d \
./protobuf/api/ignored.d \
./protobuf/api/key_change.d \
./protobuf/api/update_begin.d \
./protobuf/api/update_done.d \
./protobuf/api/update_ready.d \
./protobuf/api/variable_request.d \
./protobuf/api/variable_value.d 


# Each subdirectory must supply rules for building sources it contributes
protobuf/api/%.o: ../protobuf/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -I"../libraries/CMSIS/Include" -I"../libraries/CMSIS/Device/ST/STM32F10x/Include" -I"../libraries/STM32F10x_StdPeriph_Driver/inc" -I"../libraries/STM32_USB-FS-Device_Driver/inc" -I"../libraries/CC3000_Host_Driver" -I"../libraries/Tropicssl/include" -I"../protobuf/api" -I"../inc" -Os -ffunction-sections -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


