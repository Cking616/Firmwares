################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
PD4Master.obj: ../PD4Master.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/FreeRTOS/Source/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="PD4Master.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/FreeRTOS/Source/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_ccs.obj: ../startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/FreeRTOS/Source/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


