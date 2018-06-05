################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./PG2Slave.obj" \
"./main.obj" \
"./period.obj" \
"./startup_ccs.obj" \
"./bsp/Bumper.obj" \
"./bsp/CO_driver.obj" \
"./bsp/MA3encoder.obj" \
"./bsp/delay.obj" \
"./bsp/driver.obj" \
"./bsp/io.obj" \
"./bsp/sonar.obj" \
"./third_party/CanFestival/src/dcf.obj" \
"./third_party/CanFestival/src/emcy.obj" \
"./third_party/CanFestival/src/lifegrd.obj" \
"./third_party/CanFestival/src/lss.obj" \
"./third_party/CanFestival/src/nmtMaster.obj" \
"./third_party/CanFestival/src/nmtSlave.obj" \
"./third_party/CanFestival/src/objacces.obj" \
"./third_party/CanFestival/src/pdo.obj" \
"./third_party/CanFestival/src/sdo.obj" \
"./third_party/CanFestival/src/states.obj" \
"./third_party/CanFestival/src/sync.obj" \
"./third_party/CanFestival/src/timer.obj" \
"./utils/uartstdio.obj" \
"C:/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl/timers/timers_ccs.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/ti/TivaWare_C_Series-2.1.4.178/driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include bsp/subdir_vars.mk
-include third_party/CanFestival/src/subdir_vars.mk
-include utils/subdir_vars.mk
-include subdir_rules.mk
-include bsp/subdir_rules.mk
-include third_party/CanFestival/src/subdir_rules.mk
-include utils/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
launchpad.out \

EXE_OUTPUTS__QUOTED += \
"launchpad.out" \

BIN_OUTPUTS += \
launchpad.bin \

BIN_OUTPUTS__QUOTED += \
"launchpad.bin" \


# All Target
all: launchpad.out

# Tool invocations
launchpad.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual -z -m"timers_ccs.map" --heap_size=0 --stack_size=256 -i"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/lib" -i"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="launchpad_linkInfo.xml" --rom_model -o "launchpad.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

launchpad.bin: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armhex"  -o "launchpad.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "PG2Slave.obj" "main.obj" "period.obj" "startup_ccs.obj" "bsp\Bumper.obj" "bsp\CO_driver.obj" "bsp\MA3encoder.obj" "bsp\delay.obj" "bsp\driver.obj" "bsp\io.obj" "bsp\sonar.obj" "third_party\CanFestival\src\dcf.obj" "third_party\CanFestival\src\emcy.obj" "third_party\CanFestival\src\lifegrd.obj" "third_party\CanFestival\src\lss.obj" "third_party\CanFestival\src\nmtMaster.obj" "third_party\CanFestival\src\nmtSlave.obj" "third_party\CanFestival\src\objacces.obj" "third_party\CanFestival\src\pdo.obj" "third_party\CanFestival\src\sdo.obj" "third_party\CanFestival\src\states.obj" "third_party\CanFestival\src\sync.obj" "third_party\CanFestival\src\timer.obj" "utils\uartstdio.obj" 
	-$(RM) "PG2Slave.d" "main.d" "period.d" "startup_ccs.d" "bsp\Bumper.d" "bsp\CO_driver.d" "bsp\MA3encoder.d" "bsp\delay.d" "bsp\driver.d" "bsp\io.d" "bsp\sonar.d" "third_party\CanFestival\src\dcf.d" "third_party\CanFestival\src\emcy.d" "third_party\CanFestival\src\lifegrd.d" "third_party\CanFestival\src\lss.d" "third_party\CanFestival\src\nmtMaster.d" "third_party\CanFestival\src\nmtSlave.d" "third_party\CanFestival\src\objacces.d" "third_party\CanFestival\src\pdo.d" "third_party\CanFestival\src\sdo.d" "third_party\CanFestival\src\states.d" "third_party\CanFestival\src\sync.d" "third_party\CanFestival\src\timer.d" "utils\uartstdio.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-"C:/ti/ccsv7/utils/tiobj2bin/tiobj2bin" "launchpad.out" "launchpad.bin" "C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armofd" "C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armhex" "C:/ti/ccsv7/utils/tiobj2bin/mkhex4bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

