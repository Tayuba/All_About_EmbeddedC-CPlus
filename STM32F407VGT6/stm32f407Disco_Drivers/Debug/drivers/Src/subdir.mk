################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/stm32f407_GPIO_Driver.c \
../drivers/Src/stm32f407_SPI_Driver.c 

OBJS += \
./drivers/Src/stm32f407_GPIO_Driver.o \
./drivers/Src/stm32f407_SPI_Driver.o 

C_DEPS += \
./drivers/Src/stm32f407_GPIO_Driver.d \
./drivers/Src/stm32f407_SPI_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/%.o drivers/Src/%.su drivers/Src/%.cyclo: ../drivers/Src/%.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/All_About_EmbeddedC-C++/STM32F407VGT6/stm32f407Disco_Drivers/drivers/Inc" -I"D:/All_About_EmbeddedC-C++/STM32F407VGT6/stm32f407Disco_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-Src

clean-drivers-2f-Src:
	-$(RM) ./drivers/Src/stm32f407_GPIO_Driver.cyclo ./drivers/Src/stm32f407_GPIO_Driver.d ./drivers/Src/stm32f407_GPIO_Driver.o ./drivers/Src/stm32f407_GPIO_Driver.su ./drivers/Src/stm32f407_SPI_Driver.cyclo ./drivers/Src/stm32f407_SPI_Driver.d ./drivers/Src/stm32f407_SPI_Driver.o ./drivers/Src/stm32f407_SPI_Driver.su

.PHONY: clean-drivers-2f-Src

