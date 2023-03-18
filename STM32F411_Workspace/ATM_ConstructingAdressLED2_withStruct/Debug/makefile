################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := ATM_ConstructingAdressLED2_withStruct
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ATM_ConstructingAdressLED2_withStruct.elf \

MAP_FILES += \
ATM_ConstructingAdressLED2_withStruct.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ATM_ConstructingAdressLED2_withStruct.list \


# All Target
all: main-build

# Main-build Target
main-build: ATM_ConstructingAdressLED2_withStruct.elf secondary-outputs

# Tool invocations
ATM_ConstructingAdressLED2_withStruct.elf ATM_ConstructingAdressLED2_withStruct.map: $(OBJS) $(USER_OBJS) D:\All_About_EmbeddedC-C++\STM32F411_Workspace\ATM_ConstructingAdressLED2_withStruct\STM32F411RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ATM_ConstructingAdressLED2_withStruct.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\All_About_EmbeddedC-C++\STM32F411_Workspace\ATM_ConstructingAdressLED2_withStruct\STM32F411RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ATM_ConstructingAdressLED2_withStruct.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ATM_ConstructingAdressLED2_withStruct.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ATM_ConstructingAdressLED2_withStruct.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ATM_ConstructingAdressLED2_withStruct.elf ATM_ConstructingAdressLED2_withStruct.list ATM_ConstructingAdressLED2_withStruct.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
