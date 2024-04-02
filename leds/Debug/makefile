################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include mbed-os/subdir.mk
-include subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := leds
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: leds.axf

# Tool invocations
leds.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -o "leds.axf" $(OBJS) $(USER_OBJS) $(LIBS) -L"/home/phatt/University/apps/lcd-1-prep/apps-workspace.mcu/leds/mbed-os/lib" -DMBED_DEBUG -DMBED_TRAP_ERRORS_ENABLED=1 -DMBED_MINIMAL_PRINTF -Wl,-n -Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys -lmbed-os -Wl,--end-group -Xlinker -Map="leds.map" -Xlinker --no-warn-rwx-segment -Xlinker -print-memory-usage -Xlinker --gc-sections -Xlinker --wrap=main -Xlinker --wrap=__malloc_r -Xlinker --wrap=__free_r -Xlinker --wrap=__realloc_r -Xlinker --wrap=_memalign_r -Xlinker --wrap=_calloc_r -Xlinker --wrap=exit -Xlinker --wrap=atexit -Xlinker --wrap=printf -Xlinker --wrap=sprintf -Xlinker --wrap=snprintf -Xlinker --wrap=vprintf -Xlinker --wrap=vsprintf -Xlinker --wrap=vsnprintf -Xlinker --wrap=fprintf -Xlinker --wrap=vfprintf -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -T /home/phatt/University/apps/lcd-1-prep/apps-workspace.mcu/leds/Debug/linker-script-debug.ld -lmbed-os -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) leds.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "leds.axf" ; arm-none-eabi-objcopy -v -O binary "leds.axf" "leds.bin" ; checksum -p MK64FN1M0xxx12 -d "leds.bin"
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
