################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/5ATM_SPI_Tx_test.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/5ATM_SPI_Tx_test.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/5ATM_SPI_Tx_test.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/All_About_EmbeddedC-C++/STM32F407VGT6/stm32f407Disco_Drivers/drivers/Inc" -I"D:/All_About_EmbeddedC-C++/STM32F407VGT6/stm32f407Disco_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/5ATM_SPI_Tx_test.cyclo ./Src/5ATM_SPI_Tx_test.d ./Src/5ATM_SPI_Tx_test.o ./Src/5ATM_SPI_Tx_test.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

