
# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/Tropicssl/library/aes.c \
../libraries/Tropicssl/library/arc4.c \
../libraries/Tropicssl/library/base64.c \
../libraries/Tropicssl/library/bignum.c \
../libraries/Tropicssl/library/camellia.c \
../libraries/Tropicssl/library/certs.c \
../libraries/Tropicssl/library/debug.c \
../libraries/Tropicssl/library/des.c \
../libraries/Tropicssl/library/dhm.c \
../libraries/Tropicssl/library/havege.c \
../libraries/Tropicssl/library/md2.c \
../libraries/Tropicssl/library/md4.c \
../libraries/Tropicssl/library/md5.c \
../libraries/Tropicssl/library/padlock.c \
../libraries/Tropicssl/library/rsa.c \
../libraries/Tropicssl/library/sha1.c \
../libraries/Tropicssl/library/sha2.c \
../libraries/Tropicssl/library/sha4.c \
../libraries/Tropicssl/library/ssl_cli.c \
../libraries/Tropicssl/library/ssl_srv.c \
../libraries/Tropicssl/library/ssl_tls.c \
../libraries/Tropicssl/library/timing.c \
../libraries/Tropicssl/library/x509parse.c \
../libraries/Tropicssl/library/xtea.c 

OBJS += \
./libraries/Tropicssl/library/aes.o \
./libraries/Tropicssl/library/arc4.o \
./libraries/Tropicssl/library/base64.o \
./libraries/Tropicssl/library/bignum.o \
./libraries/Tropicssl/library/camellia.o \
./libraries/Tropicssl/library/certs.o \
./libraries/Tropicssl/library/debug.o \
./libraries/Tropicssl/library/des.o \
./libraries/Tropicssl/library/dhm.o \
./libraries/Tropicssl/library/havege.o \
./libraries/Tropicssl/library/md2.o \
./libraries/Tropicssl/library/md4.o \
./libraries/Tropicssl/library/md5.o \
./libraries/Tropicssl/library/padlock.o \
./libraries/Tropicssl/library/rsa.o \
./libraries/Tropicssl/library/sha1.o \
./libraries/Tropicssl/library/sha2.o \
./libraries/Tropicssl/library/sha4.o \
./libraries/Tropicssl/library/ssl_cli.o \
./libraries/Tropicssl/library/ssl_srv.o \
./libraries/Tropicssl/library/ssl_tls.o \
./libraries/Tropicssl/library/timing.o \
./libraries/Tropicssl/library/x509parse.o \
./libraries/Tropicssl/library/xtea.o 

C_DEPS += \
./libraries/Tropicssl/library/aes.d \
./libraries/Tropicssl/library/arc4.d \
./libraries/Tropicssl/library/base64.d \
./libraries/Tropicssl/library/bignum.d \
./libraries/Tropicssl/library/camellia.d \
./libraries/Tropicssl/library/certs.d \
./libraries/Tropicssl/library/debug.d \
./libraries/Tropicssl/library/des.d \
./libraries/Tropicssl/library/dhm.d \
./libraries/Tropicssl/library/havege.d \
./libraries/Tropicssl/library/md2.d \
./libraries/Tropicssl/library/md4.d \
./libraries/Tropicssl/library/md5.d \
./libraries/Tropicssl/library/padlock.d \
./libraries/Tropicssl/library/rsa.d \
./libraries/Tropicssl/library/sha1.d \
./libraries/Tropicssl/library/sha2.d \
./libraries/Tropicssl/library/sha4.d \
./libraries/Tropicssl/library/ssl_cli.d \
./libraries/Tropicssl/library/ssl_srv.d \
./libraries/Tropicssl/library/ssl_tls.d \
./libraries/Tropicssl/library/timing.d \
./libraries/Tropicssl/library/x509parse.d \
./libraries/Tropicssl/library/xtea.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Tropicssl/library/%.o: ../libraries/Tropicssl/library/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -I"../libraries/CMSIS/Include" -I"../libraries/CMSIS/Device/ST/STM32F10x/Include" -I"../libraries/STM32F10x_StdPeriph_Driver/inc" -I"../libraries/STM32_USB-FS-Device_Driver/inc" -I"../libraries/CC3000_Host_Driver" -I"../libraries/Tropicssl/include" -I"../protobuf/api" -I"../inc" -Os -ffunction-sections -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


